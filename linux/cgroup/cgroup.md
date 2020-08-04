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

------

**cgroup规则**

* 任何单一子系统（比如 `cpu`）最多可附加到一个层级中。

  ![RMG-rule1](D:\work_space\code\linux\cgroup\doc\RMG-rule1.png)

  

* 单一层级可附加一个或者多个子系统。

  ![RMG-rule2](D:\work_space\code\linux\cgroup\doc\RMG-rule2.png)



* 每次在系统中创建新层级时，该系统中的所有任务都是那个层级的默认 cgroup（我们称之为 *root cgroup*）的初始成员。对于您创建的任何单一层级，该系统中的每个任务都可以是那个层级中*唯一一个* cgroup 的成员。单一任务可以是在多个 cgroup 中，只要每个 cgroup 都在不同的层级中即可。只要某个任务成为同一层级中第二个 cgroup 的成员，就会将其从那个层级的第一个 cgroup 中删除。一个任务永远不会同时位于同一层级的不同 cgroup 中。

  ![](D:\work_space\code\linux\cgroup\doc\RMG-rule3.png)



* 该系统中的任意进程（任务）都将自己分支创建子进程（任务）。该子任务自动成为其父进程所在 cgroup 的成员。然后可根据需要将该子任务移动到不同的 cgroup 中，但开始时它总是继承其父任务的 cgroup（进程术语中称其为“环境”）。

  ![](D:\work_space\code\linux\cgroup\doc\RMG-rule4.png)