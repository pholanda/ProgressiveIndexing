//#include "../include/cracking/rewired_cracking.h"
//#include "../include/util/rewiring.h"
//
//constexpr std::size_t NUM_STEPS = 4;
//constexpr std::size_t PAGESIZE = 4096;
//const bool UseHugepages = true;
//
//
//bool verify_partition(const int64_t *begin, const int64_t *mid, const int64_t *end)
//{
//    int64_t max_lo{std::numeric_limits<int64_t>::lowest()};
//    int64_t min_hi{std::numeric_limits<int64_t>::max()};
//    assert(max_lo < min_hi);
//    for (const int64_t *p = begin; p != mid; ++p)
//        max_lo = std::max(max_lo, *p);
//    for (const int64_t *p = mid; p != end; ++p)
//        min_hi = std::min(min_hi, *p);
//    return max_lo <= min_hi;
//}
//
//int64_t * crackInTwoRewired(const int64_t pivot, int64_t *begin, int64_t *end,
//        rewiring::memory_mapping<UseHugepages, CHUNK_SIZE> &data,
//        rewiring::memory_mapping<UseHugepages, CHUNK_SIZE> &vm_buffer)
//{
//    assert(vm_buffer.size == 4 * CHUNK_SIZE && "buffer of wrong size");
//    using namespace rewiring;
//    constexpr std::size_t ELEMENTS_PER_CHUNK = CHUNK_SIZE / sizeof(int64_t);
//
//    int64_t * const p_buffer = static_cast<int64_t*>(vm_buffer.addr);
//    int64_t * const p_buffer_lo_begin = p_buffer + 0 * ELEMENTS_PER_CHUNK;
//    int64_t * const p_buffer_hi_end = p_buffer + 4 * ELEMENTS_PER_CHUNK;
//
//    enum {
//        BUFFER_LO_FIRST  = 0,
//        BUFFER_LO_SECOND = 1,
//        BUFFER_HI_SECOND = 2,
//        BUFFER_HI_FIRST  = 3,
//    };
//
//    /* Define pointers. */
//    int64_t *p_buf_lo = p_buffer_lo_begin;
//    int64_t *p_buf_hi = p_buffer_hi_end;
//
//    int64_t * const p_data = static_cast<int64_t*>(data.addr);
//
//    const std::size_t chunk_lo_begin = (begin - p_data) / ELEMENTS_PER_CHUNK;
//    const std::size_t chunk_hi_end   = (end - p_data - 1) / ELEMENTS_PER_CHUNK;
//    assert(p_data + chunk_lo_begin * ELEMENTS_PER_CHUNK <= begin);
//    assert(end <= p_data + (chunk_hi_end + 1) * ELEMENTS_PER_CHUNK);
//    assert(p_data + chunk_hi_end * ELEMENTS_PER_CHUNK < end);
//    std::size_t next_chunk_lo = chunk_lo_begin;
//    std::size_t next_chunk_hi = chunk_hi_end;
//    assert(p_data + next_chunk_lo * ELEMENTS_PER_CHUNK <= begin);
//    assert(p_data + (next_chunk_lo + 1) * ELEMENTS_PER_CHUNK > begin);
//    assert(p_data + next_chunk_hi * ELEMENTS_PER_CHUNK < end);
//    assert(p_data + (next_chunk_hi + 1) * ELEMENTS_PER_CHUNK >= end);
//
//    int64_t *p_src_lo = p_data + next_chunk_lo * ELEMENTS_PER_CHUNK;
//    int64_t *p_src_hi = p_data + next_chunk_hi * ELEMENTS_PER_CHUNK;
//
//    auto store = [](void *dest, int64_t &value) {
//            *((int64_t*) dest) = value;
////            }
//    };
//    auto insert = [&](int64_t &value) {
//            if (value < pivot)
//                *p_buf_lo++ = value;
//            else
//                *--p_buf_hi = value;
//
//    };
//
//    bool isFirst;
//    bool fromLo;
//
//    {
//        /* memcpy portions outside [begin,end) to the buffers */
//        int64_t * const start_lo = p_data + next_chunk_lo * ELEMENTS_PER_CHUNK;
//        int64_t * const end_hi = p_data + (next_chunk_hi + 1) * ELEMENTS_PER_CHUNK;
//        assert(begin - start_lo < long(ELEMENTS_PER_CHUNK));
//        assert(end_hi - end < long(ELEMENTS_PER_CHUNK));
//
//        if (start_lo != begin) {
//            for (auto p = start_lo; p != begin; ++p) {
//                assert(*p < pivot);
//                store(p_buf_lo++, *p);
//            }
//        }
//        if (end_hi != end) {
//            for (auto p = end_hi; p != end; --p) {
//                assert(p[-1] >= pivot);
//                store(--p_buf_hi, p[-1]);
//            }
//        }
//
//        /* partition the rest of the pages */
//        if (next_chunk_lo == next_chunk_hi) {
//            for (auto p = begin; p != end; ++p) {
//                insert(*p);
//            }
//            p_src_lo += ELEMENTS_PER_CHUNK;
//        } else {
//            if (start_lo != begin) {
//                for (auto p = begin; p != start_lo + ELEMENTS_PER_CHUNK; ++p) {
//                    insert(*p);
//                }
//                p_src_lo += ELEMENTS_PER_CHUNK;
//            }
//            if (end_hi != end) {
//                for (auto p = end_hi - ELEMENTS_PER_CHUNK; p != end; ++p) {
//                    insert(*p);
//                }
//                p_src_hi -= ELEMENTS_PER_CHUNK;
//            }
//        }
//
//
//        /* If one page of a buffer has been filled, swap the virtual memory region of this buffer into the virtual
//         * memory region of the input data. */
//        const bool is_full_lo = p_buf_lo - p_buffer_lo_begin >= long(ELEMENTS_PER_CHUNK);
//        const bool is_full_hi = p_buffer_hi_end - p_buf_hi >= long(ELEMENTS_PER_CHUNK);
//        if (is_full_lo) {
//            swap(vm_buffer, BUFFER_LO_FIRST, data, next_chunk_lo);
//            swap(vm_buffer, BUFFER_LO_FIRST, vm_buffer, BUFFER_LO_SECOND);
//            p_buf_lo -= ELEMENTS_PER_CHUNK;
//            ++next_chunk_lo;
//        }
//        if (is_full_hi) {
//            swap(vm_buffer, BUFFER_HI_FIRST, data, next_chunk_hi);
//            swap(vm_buffer, BUFFER_HI_FIRST, vm_buffer, BUFFER_HI_SECOND);
//            p_buf_hi += ELEMENTS_PER_CHUNK;
//            --next_chunk_hi;
//        }
//
//
//        if (is_full_lo and is_full_hi) {
//            isFirst = true;
//            fromLo = true;
//        } else if (is_full_lo) {
//            isFirst = false;
//            fromLo = true;
//        } else if (is_full_hi) {
//            isFirst = false;
//            fromLo = false;
//        } else {
//            isFirst = start_lo == begin and end_hi == end;
//            fromLo = start_lo == begin;
//        }
//    }
//
//    /* Repeatedly partiton a chunk at a time into the buffers.  Rewire buffers if they run full. */
//    while (p_src_lo <= p_src_hi) {
//        int64_t *p_src = fromLo ? p_src_lo : p_src_hi;
//        assert((p_src - p_data) % ELEMENTS_PER_CHUNK == 0);
//
//        /* Partition one chunk from the input data into buffer_lo/buffer_hi. */
//        for (const int64_t *end = p_src + ELEMENTS_PER_CHUNK; p_src != end; ++p_src)
//            insert(*p_src);
//
//
//        /* Update pointers. */
//        if (not fromLo)
//            p_src -= 2lu * ELEMENTS_PER_CHUNK;
//        (fromLo ? p_src_lo : p_src_hi) = p_src;
//
//        /* If one page of a buffer has been filled, swap the virtual memory region of this buffer into the virtual
//         * memory region of the input data. */
//        const bool is_full_lo = p_buf_lo - p_buffer_lo_begin >= long(ELEMENTS_PER_CHUNK);
//        const bool is_full_hi = p_buffer_hi_end - p_buf_hi >= long(ELEMENTS_PER_CHUNK);
//        if (is_full_lo) {
//            assert(p_src_lo >= p_data + (next_chunk_lo + 1) * ELEMENTS_PER_CHUNK);
//            swap(vm_buffer, BUFFER_LO_FIRST, data, next_chunk_lo);
//            swap(vm_buffer, BUFFER_LO_FIRST, vm_buffer, BUFFER_LO_SECOND);
//            p_buf_lo -= ELEMENTS_PER_CHUNK;
//            ++next_chunk_lo;
//        }
//        if (is_full_hi) {
//            assert(p_src_hi + ELEMENTS_PER_CHUNK <= p_data + next_chunk_hi * ELEMENTS_PER_CHUNK);
//            swap(vm_buffer, BUFFER_HI_FIRST, data, next_chunk_hi);
//            swap(vm_buffer, BUFFER_HI_FIRST, vm_buffer, BUFFER_HI_SECOND);
//            p_buf_hi += ELEMENTS_PER_CHUNK;
//            --next_chunk_hi;
//        }
//
//
//        if (isFirst and not is_full_lo and not is_full_hi) {
//            isFirst = false;
//            fromLo = not fromLo;
//        } else if (is_full_lo and is_full_hi) {
//            isFirst = true;
//            fromLo = true;
//        } else if (is_full_lo)
//            fromLo = true;
//        else if (is_full_hi)
//            fromLo = false;
//    }
//
//    const std::size_t num_elements_buffer_lo = p_buf_lo - p_buffer_lo_begin;
//    const std::size_t num_elements_buffer_hi = p_buffer_hi_end - p_buf_hi;
//
//    assert(num_elements_buffer_lo < ELEMENTS_PER_CHUNK);
//    assert(num_elements_buffer_hi < ELEMENTS_PER_CHUNK);
//
//    std::size_t next_chunk = fromLo ? next_chunk_lo : next_chunk_hi;
//    int64_t *partition = p_data + next_chunk * ELEMENTS_PER_CHUNK + num_elements_buffer_lo;
//    assert(num_elements_buffer_lo != 0 or num_elements_buffer_hi == 0);
//    if (num_elements_buffer_lo != 0 or num_elements_buffer_hi != 0) {
//        assert(begin <= partition);
//        assert(partition <= end);
//
//        /* Merge buffer_hi into buffer_lo.  This will exactly fill the first page of buffer_lo. */
//        assert(num_elements_buffer_lo + num_elements_buffer_hi == ELEMENTS_PER_CHUNK);
//        std::memcpy(p_buf_lo, p_buf_hi, sizeof(int64_t) * num_elements_buffer_hi);
//        assert(verify_partition(p_buffer_lo_begin, p_buf_lo, p_buffer_lo_begin + ELEMENTS_PER_CHUNK));
//        assert(*p_buf_lo >= pivot);
//        assert(*(p_buf_lo - 1) < pivot);
//
//        /* Swap the first page of buffer_lo into the virtual address space of the data. */
//        assert(vm_buffer.addr == (void*) p_buffer_lo_begin);
//        swap(vm_buffer, BUFFER_LO_FIRST, data, next_chunk);
//
//        assert(*partition >= pivot);
//        assert(*(partition - 1) < pivot);
//
//    }
//
//    return partition;
//}
//
//
////AvlTree rewiredCracking(IndexEntry *&c, int dataSize, AvlTree T, int lowKey, int highKey) {
//AvlTree rewiredCracking(rewiring::memory_mapping<UseHugepages, CHUNK_SIZE> &data, rewiring::memory_mapping<UseHugepages, CHUNK_SIZE> &vm_buffer, int dataSize, AvlTree T, int lowKey, int highKey) {
//
//    IntPair p1, p2;
//
//    p1 = FindNeighborsLT(lowKey, T, dataSize - 1);
//    IntPair pivot_pair = NULL;
//    pivot_pair = (IntPair) malloc(sizeof(struct int_pair));
//    crackInTwoRewired(lowKey, &p1->first, &p1->second, data, vm_buffer);
////    pivot_pair->first = crackInTwoPredicated(c, p1->first, p1->second, lowKey);
//    T = Insert(pivot_pair->first, lowKey, T);
//    p2 = FindNeighborsLT(highKey, T, dataSize - 1);
////    pivot_pair->second = crackInTwoPredicated(c, p2->first, p2->second, highKey);
//    T = Insert(pivot_pair->second, highKey, T);
//    free(p1);
//    free(p2);
//    if (pivot_pair) {
//        free(pivot_pair);
//        pivot_pair = NULL;
//    }
//    return T;
//}