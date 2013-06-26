#ifdef __cplusplus
extern "C" {
#endif

/// Handle for a kodo codec
typedef struct kodo_codec_ kodo_codec;

kodo_codec* kodo_new_codec();

void kodo_delete_codec(kodo_codec* codec);


#ifdef __cplusplus
}
#endif




