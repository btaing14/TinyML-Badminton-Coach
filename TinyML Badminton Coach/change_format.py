import pandas as pd
from pathlib import Path

INPUT_ROOT = Path("data")
OUTPUT_ROOT = Path("dataset_edgeimpulse")

SAMPLE_PERIOD_MS = 10

for csv_file in INPUT_ROOT.rglob("*.csv"):

    relative_path = csv_file.relative_to(INPUT_ROOT)
    output_file = OUTPUT_ROOT / relative_path

    output_file.parent.mkdir(parents=True, exist_ok=True)

    df = pd.read_csv(csv_file)

    if "timestamp" not in df.columns:
        df.insert(
            0,
            "timestamp",
            [i * SAMPLE_PERIOD_MS for i in range(len(df))]
        )

    df.to_csv(output_file, index=False)

print("Finished!")