#ifndef KTH_H
#define KTH_H
#define Parent(i) (((i) - 1) >> 1)
#define LChild(i) (1 + ((i) << 1))
#define RChild(i) ((1 + (i)) << 1)

#ifdef __cplusplus
extern "C" {
#endif
	
	int compare(int x, int y, int z, int u, int v, int w);
	
	void get_kth(int n, int k, int *x, int *y, int *z);
	
#ifdef __cplusplus
}
#endif

#endif
