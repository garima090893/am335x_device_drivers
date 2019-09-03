#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x5784715, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xa2863aaa, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xf4cc32fc, __VMLINUX_SYMBOL_STR(class_destroy) },
	{ 0x212549ed, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0x9623d3ac, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x200d68d7, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x91fac5e1, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xa02020a9, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "3B4FDF25863DC30BC672D6A");
