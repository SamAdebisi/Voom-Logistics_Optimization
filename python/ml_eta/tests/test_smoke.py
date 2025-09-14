from fastapi.testclient import TestClient
from ml_eta.service import app

client = TestClient(app)


def test_ok():
    r = client.get("/health")
    assert r.status_code == 200
    assert r.json()["ok"] is True


def test_predict_baseline():
    body = {"path": [1, 2, 3]}
    r = client.post("/predict_eta", json=body)
    assert r.status_code == 200
    data = r.json()
    assert "eta" in data and data["eta"] > 0


def test_predict_with_feats():
    body = {"path": [1, 2, 3, 4], "features": [4, 1.2, 1.1]}
    r = client.post("/predict_eta", json=body)
    assert r.status_code == 200
    assert r.json()["eta"] > 0