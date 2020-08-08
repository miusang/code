`cpu` 子系统调度对 cgroup 的 CPU 访问。可根据以下参数调度对 CPU 资源的访问，每个参数都独立存在于 cgroup 虚拟文件系统的*伪文件*中：

- cpu.shares

  包含用来指定在 cgroup 中的任务可用的相对共享 CPU 时间的整数值。例如：在两个 cgroup 中都将 `cpu.shares` 设定为 `1` 的任务将有相同的 CPU 时间，但在 cgroup 中将 `cpu.shares` 设定为 `2` 的任务可使用的 CPU 时间是在 cgroup 中将 `cpu.shares` 设定为 `1` 的任务可使用的 CPU 时间的两倍。

- cpu.rt_runtime_us

  以微秒（µs，这里以“us”代表）为单位指定在某个时间段中 cgroup 中的任务对 CPU 资源的最长连续访问时间。建立这个限制是为了防止一个 cgroup 中的任务独占 CPU 时间。如果 cgroup 中的任务应该可以每 5 秒中可有 4 秒时间访问 CPU 资源，请将 `cpu.rt_runtime_us` 设定为 `4000000`，并将 `cpu.rt_period_us` 设定为 `5000000`。

- cpu.rt_period_us

  以微秒（µs，这里以“us”代表）为单位指定在某个时间段中 cgroup 对 CPU 资源访问重新分配的频率。如果某个 cgroup 中的任务应该每 5 秒钟有 4 秒时间可访问 CPU 资源，则请将 `cpu.rt_runtime_us` 设定为 `4000000`，并将 `cpu.rt_period_us` 设定为 `5000000`。

```
mkdir /sys/fs/cgroup/cpu/test
echo 50000 > /sys/fs/cgroup/cpu/test/cpu.cfs_quota_us
echo 100000 > /sys/fs/cgroup/cpu/test/cpu.cfs_period_us
echo $pid > /sys/fs/cgroup/cpu/test/tasks
```

