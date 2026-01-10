import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("results/simulation.csv")

plt.figure(figsize=(10, 6))

plt.plot(
    df["time"],
    df["created"],
    label="Created Packets"
)

plt.plot(
    df["time"],
    df["delivered"],
    label="Delivered Packets"
)

plt.plot(
    df["time"],
    df["waiting"],
    label="Waiting Packets"
)

plt.xlabel("Time Tick")
plt.ylabel("Packets")
plt.title("Packet Flow Over Time")

plt.legend()
plt.grid(True)

plt.show()


plt.figure(figsize=(10,6))

plt.plot(
    df["time"],
    df["avg_latency"]
)

plt.xlabel("Time Tick")
plt.ylabel("Latency")

plt.title("Average Packet Latency")

plt.grid(True)

plt.show()