#ifndef PROGRESSIVEINDEXING_CONSTANTS_H
#define PROGRESSIVEINDEXING_CONSTANTS_H

#define PAGESIZE 4096.0
#define ELEMENTS_PER_PAGE (PAGESIZE / sizeof(int64_t))

#define WRITE_ONE_PAGE_SEQ_MS 0.0161349
#define READ_ONE_PAGE_SEQ_MS 0.00100697
#define READ_ONE_PAGE_WITHOUT_CHECKS_SEQ_MS 0.0005048
#define RANDOM_ACCESS_PAGE_MS 3.62e-06
#define SWAP_COST_PAGE_MS 0.0030399
#define BUCKET_ONE_PAGE_MS 0.0353779
#define BUCKET_ONE_PAGE_EQUIHEIGHT_MS 0.0298009
#define LSD_RADIXSORT_BUCKETING_PAGE_MS 0.0318274
#define LSD_RADIXSORT_COPY_ONE_PAGE_MS 0.0408376


#endif //PROGRESSIVEINDEXING_CONSTANTS_H