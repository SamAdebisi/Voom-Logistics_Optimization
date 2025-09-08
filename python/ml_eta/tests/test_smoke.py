from ml_eta.service import app

def test_ok():
    assert app.title == "Voom ML ETA"