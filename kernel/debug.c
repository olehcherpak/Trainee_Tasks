#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/fs.h>

#define LENGTH 200
#define ADDITION "World"
#define ADDITION_LENGTH 6

char ker_buf[LENGTH];
const char* mystr = " World";
ssize_t initsize;
int i, j, size;
struct dentry *dirret,*fileret;

static ssize_t myreader(struct file *fp, char __user *user_buffer,
                                size_t count, loff_t *position)
{
        return simple_read_from_buffer(user_buffer, count, position, ker_buf, LENGTH);
}

static ssize_t mywriter(struct file *fp, const char __user *user_buffer,
                                size_t count, loff_t *position)
{
        size = count + ADDITION_LENGTH;
        if (count + ADDITION_LENGTH >= LENGTH ) {
                return -EINVAL;
        }
        initsize = simple_write_to_buffer(ker_buf, LENGTH, position, user_buffer, count);
        for (i = count - 1, j = 0; i < size; i++, j++) {
                ker_buf[i] = mystr[j];
        }
        ker_buf[i] = '\n';

        return initsize;
}

static int myopen (struct inode *inode, struct file *filp)
{
        filp->private_data = inode->i_private;
        return 0;
}

static const struct file_operations fops_debug = {
        .owner = THIS_MODULE,
        .open = myopen,
        .read = myreader,
        .write = mywriter,
};

static int __init debug_init(void)
{
        dirret = debugfs_create_dir("mydir", NULL);
        if (dirret == NULL) {
                printk("Debug dir not created\n");
                return -ENOMEM;
        }
        fileret = debugfs_create_file("myfile", 0666, dirret, NULL, &fops_debug);
        if (!fileret) {
                printk("Debug file not created\n");
                return -EPERM;
        }
        printk("Debug Start\n");

        return 0;
}

static void __exit debug_exit(void)
{
        debugfs_remove_recursive(dirret);
        printk("Debug Stop\n");
}

module_init(debug_init);
module_exit(debug_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Debugfs simple test module");
MODULE_AUTHOR("Oleh Cherpak");
