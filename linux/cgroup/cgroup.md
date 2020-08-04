# Group

**cgroup**(control group)，是linux内核的一个功能，用来限制、控制与分离一个进程组的资源。

这个项目最早由Google的工程师在2006年发起，最早的名称为**进程容器**（process containers）。在2007年时，因为在linux内核中，容器（container）这个名词有许多不能的意义，为了避免混乱，被重命名为cgroup，且被合并到2.6.24版本的内核中去。

------

**cgroup子系统**：

子系统代表单一资源，如cpu时间或内存。

* **blkio** 为块设备设定输入输出限制，如物理设备（磁盘、固态硬盘、usb等）。
* **cpu** 使用调度程序提供对cpu的cgroup任务访问。
* **cpuacct** 自动生成cgroup中任务所使用的cpu报告。
* **cpuset** 为cgroup中的任务分配独立cpu和内存结点。
* **devices** 可允许或拒绝cgroup中的任务访问设备。
* **freezer** 挂起或恢复cgroup中的任务。
* **memory** 设定cgroup中任务使用的内存限制，并自动生成由那些任务使用的内存资源报告。
* **net_cls** 使用等级识别符（classid）标记网络数据包，可允许linux流量控制程序（tc）识别从具体cgroup中生成的数据包。
* **ns** 名称空间子系统。

