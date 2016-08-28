#include <ruby.h>

#define max(a, b) ((a<b) ? a : b)

typedef float float8_t __attribute__((ext_vector_type(8)));

static void*
vector_alloc(size_t ts, size_t n)
{
  void *result = NULL;
  size_t align = max(ts, sizeof(void*));
  size_t size = ts;
  size *= n;
  if(posix_memalign(&result, align, size)){
    VALUE align_e = rb_define_class("MemoryAligmentError", rb_eStandardError);
    rb_raise(align_e, "Memory could not be aligned properly");
  }
  return result;
}

float8_t*
float8_alloc(size_t n)
{
  return vector_alloc(sizeof(float8_t), n);
}

VALUE
sum(VALUE self, VALUE arg1)
{
  if(RB_TYPE_P(arg1, T_ARRAY)){
    int array_size = RARRAY_LEN(arg1);
    int packed = (array_size+7)/8;
    float8_t *vector = float8_alloc(packed);

    for(int i=0; i<packed; i++){
      for(int j=0; j<8; j++){
        if(i*8+j<array_size){
          VALUE object = RARRAY_PTR(arg1)[i+j];
          vector[i][j] = NUM2LONG(object);
        }else{
          vector[i][j] = 0;
        }
      }
    }

    float8_t vector_result = {0};
    for(int i=0; i<packed; i++){
      vector_result += vector[i];
    }

    float sum = 0;
    for(int i=0; i<8; i++){
      sum += vector_result[i];
    }

    free(vector);
    return LONG2NUM(sum);
  }

  rb_raise(rb_eArgError, "Argument should be an array");
  return Qnil;
}

void
Init_fast_sum()
{
  VALUE fast_class = rb_define_class("Fast", rb_cObject);
  rb_define_singleton_method(fast_class, "sum", sum, 1);
}
