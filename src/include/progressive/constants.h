#ifndef PROGRESSIVEINDEXING_CONSTANTS_H
#define PROGRESSIVEINDEXING_CONSTANTS_H

#define PAGESIZE 4096.0
#define ELEMENTS_PER_PAGE (PAGESIZE / sizeof(int64_t))

#define WRITE_ONE_PAGE_SEQ_MS 0.00733116
#define READ_ONE_PAGE_SEQ_MS 0.00042321
#define READ_ONE_PAGE_WITHOUT_CHECKS_SEQ_MS 0.0003561
#define RANDOM_ACCESS_PAGE_MS 9.16e-06
#define SWAP_COST_PAGE_MS 0.00295345

#define BUCKET_ONE_PAGE_MS 0.008393
#define BUCKET_ONE_PAGE_EQUIHEIGHT_MS 0.016408
#define LSD_RADIXSORT_BUCKETING_PAGE_MS 0.009579
#define LSD_RADIXSORT_COPY_ONE_PAGE_MS 0.003032




#endif //PROGRESSIVEINDEXING_CONSTANTS_H