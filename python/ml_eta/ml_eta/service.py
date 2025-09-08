from fastapi import FastAPI
from pydantic import BaseModel
from typing import List
import numpy as np

app = FastAPI(title="Voom ML ETA")

class PredictReq(BaseModel):
    path: List[int]
    features: List[float] | None = None

@app.get("/health")
def health():
    return {"ok": True}

@app.post("/predict_eta")
def predict_eta(req: PredictReq):
    n = len(req.path)
    base = n * 5.0
    return {"eta": float(base)}