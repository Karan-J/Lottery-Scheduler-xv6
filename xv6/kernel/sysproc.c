#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"
#include <stdlib.h>

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// sets the number of tickets of the calling process.
//  By default each process should get one ticket.
//  Call this function to increase/decrease the number of 
//  tickets. Return 0 if successful and -1 otherwise
//  e.g. caller function i/p < 1
int 
sys_settickets(int)
{
// to implement further. refer proc.c, proc.h
// read where round robin is implemented
// if fork() is called and child created, then child should
// have the same number of tickets as the parent.
   int n;
   if (argint(0,&n) < 0)
      return -1;
   n = 0;
   proc->tickets = n;
   return n;
//   return 0;   
}

//  implement this function to get the stats of the 
//  running process. returns some info about the running process
//  with info like how many times it is run and its PID
//  similar to ps cmd
//  Return 0 if successful and -1 otherwise
//  e.g. bad or NULL ptr passed into the kernel
int
sys_getpinfo(struct pstat*)
{
// understand how to fill in the structure pstat in kernel
// and pass the result to user space. refer pstat.h
// refer how args are passed into the read() -> sys_read(). 
// see how argptr() is used 
   return 0;
}

int 
get_random(int total_tickets)
{
  return rand()%total_tickets + 1;

}
