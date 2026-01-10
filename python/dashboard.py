import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("..results/sample_output.csv")

plt.figure(figsize=(12, 6))

plt.plot(
    df["time"],
    df["delivered"],
    linewidth=2,
    label="Delivered"
)

plt.plot(
    df["time"],
    df["created"],
    linewidth=2,
    label="Created"
)

plt.plot(
    df["time"],
    df["waiting"],
    linewidth=2,
    label="Waiting"
)

plt.plot(
    df["time"],
    df["dropped"],
    linewidth=2,
    label="Dropped"
)

plt.title("Packet Statistics")
plt.xlabel("Time")
plt.ylabel("Packets")
plt.grid(True)
plt.legend()

plt.show()


plt.figure(figsize=(12, 6))

plt.plot(
    df["time"],
    df["avg_latency"],
    linewidth=2
)

plt.title("Average Latency")
plt.xlabel("Time")
plt.ylabel("Latency")
plt.grid(True)

plt.show()


plt.figure(figsize=(12, 6))

plt.plot(
    df["time"],
    df["throughput"],
    linewidth=2
)

plt.title("Throughput")
plt.xlabel("Time")
plt.ylabel("Packets/Tick")
plt.grid(True)

plt.show()


plt.figure(figsize=(12, 6))

plt.plot(
    df["time"],
    df["packet_loss"],
    linewidth=2
)

plt.title("Packet Loss Rate")
plt.xlabel("Time")
plt.ylabel("Loss %")
plt.grid(True)

plt.show()