#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "wave_samples.h"

long get_sample(Raw_wave * wave, int nSample)
{
  long result = 0;
  if (nSample <= num_samples(wave)){
    assert(sizeof(long) >= 4);
    int blockAlign = block_align(wave);
    char * ptr = wave->data->audiodata + nSample * blockAlign;
    memcpy(&result, ptr, blockAlign); 
  }
  return result;
}

void set_sample(Raw_wave * wave, int nSample, long value)
{
  if (nSample <= num_samples(wave)){
    int blockAlign = block_align(wave);
    memcpy(wave->data->audiodata + nSample * blockAlign, &value, blockAlign);
  }
}

Linked_list * extract_samples(Raw_wave * wave)
{
  Linked_list * list = llist_create();
  int i;
  for (i = 0; i < num_samples(wave); ++i){
    llist_push(&list, i, get_sample(wave, i));
  }
  return list;
}

//TODO: now overwrites existing samples, should have options to append etc
void insert_samples(Raw_wave ** wave, Linked_list * src)
{
  free((*wave)->data->audiodata); 
  int blockAlign = block_align(*wave);
  (*wave)->data->audiodata = malloc(src->size * blockAlign);
  Node * node = src->tail; 
  int numSamples = num_samples(*wave);
  int i;
  for (i = 0; i< src->size; ++i){
    memcpy((*wave)->data->audiodata + i * blockAlign, &(node->data), blockAlign);
    node = node->next;
  }  
  //set_datasize(*wave, src->size); 
  return;
}

//void insert_samples_compl(Raw_wave ** dst, Linked_list * src, int index, int n,  overwrite)
//{
  
//}
