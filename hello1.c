
/*
 * Copyright (c) 2017, GlobalLogic Ukraine LLC
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *    This product includes software developed by the GlobalLogic.
 * 4. Neither the name of the GlobalLogic nor the
 *    names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY GLOBALLOGIC UKRAINE LLC ``AS IS`` AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL GLOBALLOGIC UKRAINE LLC BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "hello1.h"

MODULE_AUTHOR("Andriy Chuyan <majyr295@gmail.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

struct my_data {
	ktime_t start;
	ktime_t end;
	struct list_head list; 
};

extern LIST_HEAD(my_list);

int print_hello(uint parameter)
{
	if (parameter == 0 || (parameter >= 5 && parameter <= 10))
	{
		pr_warn("Parameter is 0 or ranges from 5 to 10!\n");
	}
	BUG_ON(parameter > 10);
	
	struct my_data *tmp;
	int i;
	for (i = 0; i < parameter; i++)
	{
		if (i == 7) 
		{
			tmp = 0;
		}
		else
		{
			tmp = kmalloc(sizeof(struct my_data), GFP_KERNEL);
		}
		tmp->start = ktime_get();
		pr_info("Hello, world!\n");
		tmp->end = ktime_get();
		list_add_tail(&tmp->list, &my_list);
	}
	return 0;
}
EXPORT_SYMBOL(print_hello);

static int __init hello_init(void)
{
	return 0;
}

static void __exit hello_exit(void)
{
	struct my_data *tmp, *next;
	list_for_each_entry_safe(tmp, next, &my_list, list)
	{
		pr_info("time = %lld\n", ktime_to_ns(tmp->end) - ktime_to_ns(tmp->start));
		list_del(&tmp->list);
		kfree(tmp);
	}
}

module_init(hello_init);
module_exit(hello_exit);
