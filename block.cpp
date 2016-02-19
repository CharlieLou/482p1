queue<ucontext_t*> ready;
ucontext_t * 	current;

//	global variables

atomic<bool> guard;
queue<ucontext_t*> waiting;
unsigned int count = 0;
void thread_block3(void){
	cpu::interrupt_disable();
	while(guard.exchange(true)){}
	count++;
	if(count == 3){
		for(int i = 0; i < 2; i++){
			ucontext_t* go = waiting.front();
			wait.pop();
			ready.push(go);
		}
		count = 0;
	} else {
		waiting.push(current);
		current = ready.front();
		ready.pop();
	}
	
	
