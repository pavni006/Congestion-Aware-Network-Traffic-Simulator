import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/sample_output.csv")

fig, axes = plt.subplots(
    2,
    2,
    figsize=(14, 10)
)

# Packet Statistics
axes[0, 0].plot(df["time"], df["created"], label="Created")
axes[0, 0].plot(df["time"], df["delivered"], label="Delivered")
axes[0, 0].plot(df["time"], df["waiting"], label="Waiting")
axes[0, 0].plot(df["time"], df["dropped"], label="Dropped")

axes[0, 0].set_title("Packet Statistics")
axes[0, 0].set_xlabel("Time")
axes[0, 0].set_ylabel("Packets")
axes[0, 0].grid(True)
axes[0, 0].legend()

# Average Latency
axes[0, 1].plot(df["time"], df["avg_latency"])

axes[0, 1].set_title("Average Latency")
axes[0, 1].set_xlabel("Time")
axes[0, 1].set_ylabel("Latency")
axes[0, 1].grid(True)

# Throughput
axes[1, 0].plot(df["time"], df["throughput"])

axes[1, 0].set_title("Throughput")
axes[1, 0].set_xlabel("Time")
axes[1, 0].set_ylabel("Packets / Tick")
axes[1, 0].grid(True)

# Packet Loss
axes[1, 1].plot(df["time"], df["packet_loss"])

axes[1, 1].set_title("Packet Loss Rate")
axes[1, 1].set_xlabel("Time")
axes[1, 1].set_ylabel("Loss %")
axes[1, 1].grid(True)

plt.tight_layout()
plt.show()