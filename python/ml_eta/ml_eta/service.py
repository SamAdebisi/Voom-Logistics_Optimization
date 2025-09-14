from __future__ import annotations
import os
from functools import lru_cache
from typing import List, Optional

import numpy as np
from fastapi import FastAPI, HTTPException
from pydantic import BaseModel, Field, model_validator

try:
    from xgboost import XGBRegressor
    _XGB_OK = True
except Exception:  # xgboost optional at runtime
    XGBRegressor = object  # type: ignore
    _XGB_OK = False

app = FastAPI(title="Voom ML ETA")


class PredictReq(BaseModel):
    path: List[int] = Field(min_items=1)
    # [path_len, traffic, weather]; if None, traffic=1.0, weather=1.0
    features: Optional[List[float]] = None

    @model_validator(mode="after")
    def _check_feats(self):
        if self.features is not None and len(self.features) != 3:
            raise ValueError("features must be length 3: [path_len, traffic, weather]")
        return self


class PredictResp(BaseModel):
    eta: float
    model: str


@lru_cache(maxsize=1)
def load_model() -> tuple[Optional[XGBRegressor], str]:
    path = os.getenv("MODEL_PATH", "model.json")
    if not _XGB_OK or not os.path.exists(path):
        return None, "baseline"
    m = XGBRegressor()
    m.load_model(path)
    return m, path


@app.get("/health")
def health():
    model, src = load_model()
    return {"ok": True, "model": src}


@app.post("/predict_eta", response_model=PredictResp)
def predict_eta(req: PredictReq):
    n = len(req.path)
    if req.features is None:
        feats = np.array([[float(n), 1.0, 1.0]], dtype=np.float32)
    else:
        feats = np.array([req.features], dtype=np.float32)

    model, src = load_model()
    if model is None:
        # simple baseline
        return PredictResp(eta=float(n * 5.0), model=src)
    try:
        pred = float(model.predict(feats)[0])
        if not np.isfinite(pred):
            raise ValueError("non-finite prediction")
        return PredictResp(eta=pred, model=src)
    except Exception as e:  # model inference failure -> 400
        raise HTTPException(status_code=400, detail=f"prediction_failed: {e}")


@app.post("/reload")
def reload_model():
    load_model.cache_clear()
    model, src = load_model()
    return {"ok": True, "model": src, "loaded": model is not None}