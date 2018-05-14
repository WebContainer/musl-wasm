static inline struct pthread *__pthread_self()
{
	struct pthread *self;
	return self;
}

#define TP_ADJ(p) (p)

#define REG_EIP 0
#define MC_PC regs[REG_EIP]
