#ifndef KSU_SUSFS_H
#define KSU_SUSFS_H

#include <linux/version.h>
#include <linux/types.h>
#include <linux/utsname.h>
#include <linux/hashtable.h>
#include <linux/path.h>
#include <linux/susfs_def.h>
#include <linux/mount.h>

#define SUSFS_VERSION "v2.0.0"
#if LINUX_VERSION_CODE < KERNEL_VERSION(5,0,0)
#define SUSFS_VARIANT "NON-GKI"
#else
#define SUSFS_VARIANT "GKI"
#endif

/* non shared to userspace ksu_susfs tool */
#define SYSCALL_FAMILY_ALL_ENOENT 0
#define SYSCALL_FAMILY_OPENAT 1
#define SYSCALL_FAMILY_MKNOD 2
#define SYSCALL_FAMILY_MKDIRAT 3
#define SYSCALL_FAMILY_RMDIR 4
#define SYSCALL_FAMILY_UNLINKAT 5
#define SYSCALL_FAMILY_SYMLINKAT_NEWNAME 6
#define SYSCALL_FAMILY_LINKAT_OLDNAME 7
#define SYSCALL_FAMILY_LINKAT_NEWNAME 8
#define SYSCALL_FAMILY_RENAMEAT2_OLDNAME 9
#define SYSCALL_FAMILY_RENAMEAT2_NEWNAME 10
#define SYSCALL_FAMILY_TRUNCATE 11
#define SYSCALL_FAMILY_FACCESSAT 12
#define SYSCALL_FAMILY_CHDIR 13

/*********/
/* MACRO */
/*********/
#define getname_safe(name) (name == NULL ? ERR_PTR(-EINVAL) : getname(name))
#define putname_safe(name) (IS_ERR(name) ? NULL : putname(name))

/**********/
/* STRUCT */
/**********/
/* sus_path */
#ifdef CONFIG_KSU_SUSFS_SUS_PATH
struct st_susfs_sus_path {
	unsigned long                           target_ino;
	char                                    target_pathname[SUSFS_MAX_LEN_PATHNAME];
	unsigned int                            i_uid;
	int                                     err;
};

struct st_susfs_sus_mount {
	char                    target_pathname[SUSFS_MAX_LEN_PATHNAME];
};

struct st_susfs_sus_path_list {
	struct list_head                        list;
	struct st_susfs_sus_path                info;
	char                                    target_pathname[SUSFS_MAX_LEN_PATHNAME];
	size_t                                  path_len;
};
#endif

/* sus_mount */
#ifdef CONFIG_KSU_SUSFS_SUS_MOUNT
struct st_susfs_hide_sus_mnts_for_non_su_procs {
	bool                                    enabled;
	int                                     err;
};
#endif

/* sus_kstat */
#ifdef CONFIG_KSU_SUSFS_SUS_KSTAT
struct st_susfs_sus_kstat {
	int                                     is_statically;
	unsigned long                           target_ino; // the ino after bind mounted or overlayed
	char                                    target_pathname[SUSFS_MAX_LEN_PATHNAME];
	unsigned long                           spoofed_ino;
	unsigned long                           spoofed_dev;
	unsigned int                            spoofed_nlink;
	long long                               spoofed_size;
	long                                    spoofed_atime_tv_sec;
	long                                    spoofed_mtime_tv_sec;
	long                                    spoofed_ctime_tv_sec;
	long                                    spoofed_atime_tv_nsec;
	long                                    spoofed_mtime_tv_nsec;
	long                                    spoofed_ctime_tv_nsec;
	unsigned long                           spoofed_blksize;
	unsigned long long                      spoofed_blocks;
	int                                     err;
};

struct st_susfs_sus_kstat_hlist {
	unsigned long                           target_ino;
	struct st_susfs_sus_kstat               info;
	struct hlist_node                       node;
};
#endif

/* try_umount */
#ifdef CONFIG_KSU_SUSFS_TRY_UMOUNT
struct st_susfs_try_umount {
	char                                    target_pathname[SUSFS_MAX_LEN_PATHNAME];
	int                                     mnt_mode;
	int                                     err;
};

struct st_susfs_sus_proc_fd_link {
	char                    target_link_name[SUSFS_MAX_LEN_PATHNAME];
	char                    spoofed_link_name[SUSFS_MAX_LEN_PATHNAME];
};

struct st_susfs_sus_memfd {
	char                    target_pathname[SUSFS_MAX_LEN_MFD_NAME];
};

struct st_susfs_mnt_id_recorder {
	int                     target_mnt_id[SUSFS_MAX_SUS_MNTS];
	int                     spoofed_mnt_id[SUSFS_MAX_SUS_MNTS];
	int                     spoofed_parent_mnt_id[SUSFS_MAX_SUS_MNTS];
	int                     count;
};

struct st_susfs_sus_mount_list {
	struct list_head                        list;
	struct st_susfs_sus_mount               info;
};

struct st_susfs_sus_kstat_list {
	struct list_head                        list;
	struct st_susfs_sus_kstat               info;
};

struct st_susfs_sus_maps_list {
	struct list_head                        list;
	struct st_susfs_sus_maps                info;
};

struct st_susfs_try_umount_list {
	struct list_head                        list;
	struct st_susfs_try_umount              info;
};
struct st_susfs_sus_proc_fd_link_list {
	struct list_head                        list;
	struct st_susfs_sus_proc_fd_link        info;
};

struct st_susfs_sus_memfd_list {
	struct list_head                        list;
	struct st_susfs_sus_memfd               info;
};

struct st_susfs_mnt_id_recorder_list {
	struct list_head                        list;
	int                                     pid;
	int                                     opened_count;
	struct st_susfs_mnt_id_recorder         info;
};
#endif

/* spoof_uname */
#ifdef CONFIG_KSU_SUSFS_SPOOF_UNAME
struct st_susfs_uname {
	char                                    release[__NEW_UTS_LEN+1];
	char                                    version[__NEW_UTS_LEN+1];
	int                                     err;
};
#endif

/* enable_log */
#ifdef CONFIG_KSU_SUSFS_ENABLE_LOG
struct st_susfs_log {
	bool                                    enabled;
	int                                     err;
};
#endif

/* spoof_cmdline_or_bootconfig */
#ifdef CONFIG_KSU_SUSFS_SPOOF_CMDLINE_OR_BOOTCONFIG
struct st_susfs_spoof_cmdline_or_bootconfig {
	char                                    fake_cmdline_or_bootconfig[SUSFS_FAKE_CMDLINE_OR_BOOTCONFIG_SIZE];
	int                                     err;
};
#endif

/* open_redirect */
#ifdef CONFIG_KSU_SUSFS_OPEN_REDIRECT
struct st_susfs_open_redirect {
	unsigned long                           target_ino;
	char                                    target_pathname[SUSFS_MAX_LEN_PATHNAME];
	char                                    redirected_pathname[SUSFS_MAX_LEN_PATHNAME];
	int                                     err;
};

struct st_susfs_open_redirect_hlist {
	unsigned long                           target_ino;
	char                                    target_pathname[SUSFS_MAX_LEN_PATHNAME];
	char                                    redirected_pathname[SUSFS_MAX_LEN_PATHNAME];
	struct hlist_node                       node;
};
#endif

/* sus_map */
#ifdef CONFIG_KSU_SUSFS_SUS_MAP
struct st_susfs_sus_map {
	char                                    target_pathname[SUSFS_MAX_LEN_PATHNAME];
	int                                     err;
};
#endif

/* avc log spoofing */
struct st_susfs_avc_log_spoofing {
	bool                                    enabled;
	int                                     err;
};

/* get enabled features */
struct st_susfs_enabled_features {
	char                                    enabled_features[SUSFS_ENABLED_FEATURES_SIZE];
	int                                     err;
};

/* show variant */
struct st_susfs_variant {
	char                                    susfs_variant[16];
	int                                     err;
};

/* show version */
struct st_susfs_version {
	char                                    susfs_version[16];
	int                                     err;
};

/***********************/
/* FORWARD DECLARATION */
/***********************/
/* sus_path */
#ifdef CONFIG_KSU_SUSFS_SUS_PATH
void susfs_add_sus_path(void __user **user_info);
void susfs_add_sus_path_loop(void __user **user_info);
#endif

/* sus_mount */
#ifdef CONFIG_KSU_SUSFS_SUS_MOUNT
void susfs_set_hide_sus_mnts_for_non_su_procs(void __user **user_info);
#endif // #ifdef CONFIG_KSU_SUSFS_SUS_MOUNT

/* sus_kstat */
#ifdef CONFIG_KSU_SUSFS_SUS_KSTAT
void susfs_add_sus_kstat(void __user **user_info);
void susfs_update_sus_kstat(void __user **user_info);
void susfs_sus_ino_for_generic_fillattr(unsigned long ino, struct kstat *stat);
void susfs_sus_ino_for_show_map_vma(unsigned long ino, dev_t *out_dev, unsigned long *out_ino);
#endif
/* try_umount */
#ifdef CONFIG_KSU_SUSFS_TRY_UMOUNT
void susfs_add_try_umount(void __user **user_info);
void susfs_try_umount(uid_t uid);
#endif // #ifdef CONFIG_KSU_SUSFS_TRY_UMOUNT

/* spoof_uname */
#ifdef CONFIG_KSU_SUSFS_SPOOF_UNAME
void susfs_set_uname(void __user **user_info);
void susfs_spoof_uname(struct new_utsname* tmp);
#endif

/* enable_log */
#ifdef CONFIG_KSU_SUSFS_ENABLE_LOG
void susfs_enable_log(void __user **user_info);
#endif

/* spoof_cmdline_or_bootconfig */
#ifdef CONFIG_KSU_SUSFS_SPOOF_CMDLINE_OR_BOOTCONFIG
void susfs_set_cmdline_or_bootconfig(void __user **user_info);
int susfs_spoof_cmdline_or_bootconfig(struct seq_file *m);
#endif

/* open_redirect */
#ifdef CONFIG_KSU_SUSFS_OPEN_REDIRECT
void susfs_add_open_redirect(void __user **user_info);
struct filename* susfs_get_redirected_path(unsigned long ino);
#endif

/* sus_map */
#ifdef CONFIG_KSU_SUSFS_SUS_MAP
void susfs_add_sus_map(void __user **user_info);
#endif

void susfs_set_avc_log_spoofing(void __user **user_info);
#if LINUX_VERSION_CODE < KERNEL_VERSION(4,14,0)
int susfs_sus_path_by_path(struct path* file, int* errno_to_be_changed, int syscall_family);
#else
int susfs_sus_path_by_path(const struct path* file, int* errno_to_be_changed, int syscall_family);
#endif
int susfs_sus_path_by_filename(struct filename* name, int* errno_to_be_changed, int syscall_family);
int susfs_sus_mount(struct vfsmount* mnt, struct path* root);
int susfs_sus_ino_for_filldir64(unsigned long ino);
void susfs_sus_kstat(unsigned long ino, struct stat* out_stat);
int susfs_sus_maps(unsigned long target_ino, unsigned long target_addr_size,
					unsigned long* orig_ino, dev_t* orig_dev, vm_flags_t* flags,
					unsigned long long* pgoff, struct vm_area_struct* vma, char* out_name);
void susfs_sus_map_files_readlink(unsigned long target_ino, char* pathname);
int susfs_sus_map_files_instantiate(struct vm_area_struct* vma);
int susfs_is_sus_maps_list_empty(void);
int susfs_sus_proc_fd_link(char *pathname, int len);
int susfs_is_sus_proc_fd_link_list_empty(void);
int susfs_sus_memfd(char *memfd_name);
void susfs_add_mnt_id_recorder(struct mnt_namespace *ns);
int susfs_get_fake_mnt_id(int mnt_id, int *out_mnt_id, int *out_parent_mnt_id);
void susfs_remove_mnt_id_recorder(void);

void susfs_get_enabled_features(void __user **user_info);
void susfs_show_variant(void __user **user_info);
void susfs_show_version(void __user **user_info);

void susfs_start_sdcard_monitor_fn(void);

/* susfs_init */
void susfs_init(void);

#endif
