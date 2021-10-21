#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

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

//TODO:SK
/** 
 * [PROJECT-2]: The following code is added by Shreyans (SSP210009) and Karan (KHJ200000)
 * Added two new system calls here
**/

// sets the number of tickets of the calling process.
//  By default each process should get one ticket.
//  Call this function to increase/decrease the number of 
//  tickets. Return 0 if successful and -1 otherwise
//  e.g. caller function i/p < 1
int 
sys_settickets(void)
{
  // to implement further. refer proc.c, proc.h
// read where round robin is implemented
// if fork() is called and child created, then child should
// have the same number of tickets as the parent.
//    return 0;   
    int tickets;

    if (argint(0,&tickets) < 0)
    {
      return -1;
    }

    if (tickets <= 0)
    {
      return -1;
    }
    
    proc->tickets = tickets;

    return 0;
}

int 
sys_getpinfo(void)
{
  return 0;
}
/* End of code added */