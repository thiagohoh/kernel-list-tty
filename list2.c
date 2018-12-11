#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/version.h>
#include <linux/sched/signal.h>


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thiago, Erica");
MODULE_DESCRIPTION("Show all tasks in terminal");
MODULE_VERSION("0.1");


struct task_struct *task_list; //task_struct list

static void print_string(char *str){ //Funcao para printar no terminal da onde o modulo foi chamado

struct tty_struct *my_tty;

	my_tty = get_current_tty();//pega o terminal atual

	if(my_tty != NULL){
		(my_tty->driver->ops->write) (my_tty,"\015\012",2);//escreve no terminal pra pular linha
		(my_tty->driver->ops->write) (my_tty,str,strlen(str));//escreve a msg desejada no terminal		
		(my_tty->driver->ops->write) (my_tty,"\015\012",2);
	}
}


static int __init print_string_init(void){ //funcao initial de quando o modulo for carregado

	print_string("ITS ALIVE, OH GOD ITS HORRIBLE");// printa no terminal
	printk(KERN_INFO "OOOOOOOOOBA\n"); // printa no dmesg
	for_each_process(task_list){ //itera sobre todos os processos. macro do linux
		
		print_string(task_list->comm);// printa o nome de cada task no terminal
		
	}


	return 0;
}

static void __exit print_string_exit(void){// func de unload do modulo
	print_string("ESTA MORTO O MODULO. MORTO!!");// printa no terminal
	printk(KERN_INFO "ADIOOOOOS\n");// printa no dmesg
}

module_init(print_string_init);
module_exit(print_string_exit);


