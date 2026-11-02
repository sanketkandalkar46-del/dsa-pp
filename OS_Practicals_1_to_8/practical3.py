import threading
import time

semaphore = threading.Semaphore(1)

def process(number):
    print(f"Process {number} is waiting.")
    semaphore.acquire()

    try:
        print(f"Process {number} entered critical section.")
        time.sleep(1)
        print(f"Process {number} is leaving critical section.")
    finally:
        semaphore.release()

threads = []

for i in range(1, 4):
    t = threading.Thread(target=process, args=(i,))
    threads.append(t)
    t.start()

for t in threads:
    t.join()

print("All processes completed.")
