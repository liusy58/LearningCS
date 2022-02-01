???+info "bang mechanism"
    The VM handles stack overflow by framing the stack arena with inaccessible guard pages, and intercepting the accesses to those guard pages to detect the case where a stack overflow occurred. That also requires and additional logic of actually probing the stack when putting a new activation record on it: by touching the stack down trying to trigger the guard page fault. This mechanism has a fancy name of "stack banging", and if we want to do anything below stack pointer, we need to communicate the additional banging to the runtime.




## registers
???+note "number of registers"
    |||
    |-|-|
    |`rax`|0|
    |`rcx`|1|
    |`rdx`|2|
    |`rbx`|3|
    |`rsp`|4|
    |`rbp`|5|
    |`rsi`|6|
    |`rdi`|7|
    |`r8`|8|
    |`r9`|9|
    |`r10`|10|
    |`r11`|11|
    |`r12`|12|
    |`r13`|13|    
    |`r14`|14|
    |`r15`|15|



???+note "XMM registers"
    XMM registers are separate registers introduced with SSE(Data transfer Instructions) and still widely used nowadays. They are 128 bits wide, with instructions that can treat them as arrays of 64, 32(integer and floating point), 16 or 8 bit(integer only) values. You have 8 of them in 32 bit mode, 16 in 64 bit.




``` mermaid
graph LR
  A[Start] --> B{Error?};
  B -->|Yes| C[Hmm...];
  C --> D[Debug];
  D --> B;
  B ---->|No| E[Yay!];
```


???+info "How to create a Symbol"
    `SymbolTable::new_symbols`

```java
public abstract class AbstractCoder {
    public abstract int abstractWork(byte[] data);
}

public interface Coder {
    int work(byte[] data);
}

public class Coder0 extends AbstractCoder implements Coder {
    public static int staticWork(byte[] data) {
        return data.length;
    }

    @Override
    public int work(byte[] data) {
        return data.length;
    }

    @Override
    public int abstractWork(byte[] data) {
        return data.length;
    }
}
```



```
LIR:
B1 [0, 0] sux: B0 
__id_Instruction___________________________________________
   0 label [label:0x00007f2d44363f60]
   2 std_entry 

B0 std [0, 0] preds: B1 
__id_Instruction___________________________________________
   8 label [label:0x00007f2d44363680]
  10 return   
```


```
void LIR_OpLabel::emit_code




```

const Register IC_Klass    = rax;   // where the IC klass is cached



|opcode||
|-|-|
|`0X8B`|movl|
|||


#### x86 instruction format 

<table border="1">
    <tbody><tr><td>000000</td><td>00001</td><td>00010</td><td>00011</td><td>00000</td><td>100000</td></tr>
    <tr><td>Opcode</td><td>Rs</td>   <td>Rt</td>   <td>Rd</td>   <td>Sh. Amt.</td><td>Operation</td></tr>
</tbody></table>



[x86 instruction format](http://staffwww.fullcoll.edu/aclifton/cs241/lecture-instruction-format.html)


#### X86 prefix

|prefix|||
|-|-|-|
|REX|0x4||


#### PEX prefix

<table border="1">
    <tbody><tr><th>Field</th><td colspan="4"><code>0100</code></td><td>W</td><td>R</td><td>X</td><td>B</td></tr>
    <tr><th>Bits</th><td colspan="4">7,6,5,4</td><td>3</td><td>2</td><td>1</td><td>0</td></tr>
</tbody></table>




### MacroAssembler

|||  
|-|-|
|Stack frame creation/removal|`void enter();` `void leave();`|
|||



[JVM之Klass模型](https://lonelyrookie.github.io/2020/08/22/Klass%E6%A8%A1%E5%9E%8B/)