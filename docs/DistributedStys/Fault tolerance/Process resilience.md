???+note "Group organization"
    |Type|Definition|Advantages|Disadvantages|Graph|
    |-|-|
    |Flat group| All processes are equal|No single point of failure|Complicated|<img src="../img/08-04a.png" alt="l" style="width:400px;"/>|
    |Hierarchical group|One process is the coordinator.|Easy to implement.|Loss of the coordinator brings the entire group to a grinding halt|src="../img/08-04b.png" alt="l" style="width:400px;"/>|

### Failure masking and replication

???+note "How many replicas?"
    For K falut tolerant:
    Assumption: a process does not collude with another process

    |Type of fault||
    |Fail-silent faults|K+1|
    |Byzantine faults|2K+1|

    
### Paxos


目标：proposer向3个aceptort 将name变量写为v1。
* 第一阶段A：proposer发起prepare（name，n1）,n1是递增提议版本号，发送给3个Acceptor，说，我现在要写name这个变量，我的版本号是n1
* 第一阶段B：Acceptor收到proposer的消息，比对自己内部保存的内容，发现之前name变量（null，null）没有被写入且未收到过提议，都返回给proposer，并在内部记录name这个变量，已经有proposer申请提议了，提议版本号是n1;
* 第二阶段A：proposer收到3个Acceptor的响应，响应内容都是：name变量现在还没有写入，你可以来写。proposer确认获得超过半数以上Acceptor同意，发起第二阶段写入操作：accept（v1,n1），告诉Acceptor我现在要把name变量协议v1,我的版本号是刚刚获得通过的n1;
* 第二阶段B：accpetor收到accept（v1,n1），比对自身的版本号是一致的，保存成功，并响应accepted（v1,n1）；
* 结果阶段：proposer收到3个accepted响应都成功，超过半数响应成功，到此name变量被确定为v1。

情况二：3个accpetor，但有两个proposer。proposer1和proposer2交错执行

proposer1提议accpetor1成功，但写入accpetor2和accpetor3时，发现版本号已经小于accpetor内部记录的版本号（保存了proposer2的版本号），直接返回失败。

proposer2写入accpetor2和accpetor3成功，写入accpetor1失败，但最终还是超过半数写入v2成功，name变量最终确定为v2；

proposer1递增版本号再重试发现超过半数为v2，接受name变量为v2，也不再写入v1。name最终确定还是为v2



