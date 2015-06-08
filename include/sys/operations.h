#define  PUSHALL \
        pushq %rax; \
        pushq %rbx; \
        pushq %rcx; \
        pushq %rdx; \
        pushq %rbp; \
        pushq %rdi; \
        pushq %rsi; \
        pushq %r8; \
        pushq %r9; \
        pushq %r10; \
        pushq %r11; \
        pushq %r12; \
        pushq %r13; \
        pushq %r14; \
        pushq %r15; 


#define  POPALL \
	"\tpopq %%rsp\n" \
        "\tpopq %%r15\n" \
       "\tpopq %%r14\n" \
        "\tpopq %%r13\n" \
        "\tpopq %%r12\n" \
        "\tpopq %%r11\n" \
        "\tpopq %%r10\n" \
        "\tpopq %%r9\n" \
        "\tpopq %%r8\n" \
        "\tpopq %%rsi\n" \
        "\tpopq %%rdi\n" \
        "\tpopq %%rbp\n" \
        "\tpopq %%rdx\n" \
        "\tpopq %%rcx\n" \
        "\tpopq %%rbx\n" \
        "\tpopq %%rax\n" 










