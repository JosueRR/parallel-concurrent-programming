/*
 * Copyright 2021 Josue Retana  - UCR
 * Implementation file of a dynamic container of type queue to store the factoring of each number
 * It has the special feature of storing a queue in each node to store the result of the factorization process
 */

#include "queue_data.h"
#include <stdio.h>

typedef struct queue_node {
  // value read from input stream
  int64_t element;

  // pointer to next node
  queue_node_t * next;

  // exponent of the element
  int64_t element_counter;
}queue_node_t;

void queue_data_init(queue_data_t * queue_data) {
  assert(queue_data);
  queue_data->head = NULL;
  queue_data->tail = NULL;
  queue_data->size = 0;
}

int queue_data_append(queue_data_t * queue_data, int64_t value) {
  assert(queue_data);
  int error = EXIT_SUCCESS;

  // allocate_memory(new_node)
  queue_node_t * new_node = (queue_node_t *) calloc(1, sizeof(queue_node_t));  // NOLINT

  // if the new node exists
  if (new_node) {
    // we set the attributes to their corresponding value
    new_node->element = value;
    new_node->element_counter = 1;

    // if (THE_QUEUE_IS_EMPTY):
    if (queue_data->tail == NULL) {
      // in this case the new node is the only node in the queue
      queue_data->tail = new_node;
      queue_data->head = new_node;
    } else {
      // in this case, there are more nodes and we neeed to add at the end
      queue_data->tail->next = new_node;
      queue_data->tail = queue_data->tail->next;
    }
    ++queue_data->size;
  } else {
    // if the new node doesn't exist we return 1 to show error
    error = EXIT_FAILURE;
    fprintf(stderr, "ERROR: Not enough memory to append a new element.\n");
  }
  return error;
}

int queue_data_insert(queue_data_t * current_queue, int64_t value) {
  assert(current_queue);
  int error = EXIT_SUCCESS;

  // existing_node = search_in_queue(value)
  queue_node_t * existing_value = queue_data_search(current_queue, value);
  if (existing_value) {
    // if the value is repeated we only add 1 to the element counter
    existing_value->element_counter++;
  } else {
    // if the value isn't repeated we add the new value to the queue
    error = queue_data_append(current_queue, value);
  }
  return error;
}

queue_node_t * queue_data_search(queue_data_t * current_queue,
  int64_t search_value) {
  assert(current_queue);
  queue_node_t * current = current_queue->head;
  while (current && current->element != search_value) {
    current = current->next;
  }

  // if the element isn't found a null pointer is returned
  return current;
}

void queue_data_destroy(queue_data_t * queue_data) {
  assert(queue_data);
  queue_node_t * current = queue_data->head;
  queue_node_t * temp = NULL;

  while (current) {
    temp = current->next;

    // destruction of node destroys all its attributes
    queue_node_destroy(current);
    current = temp;
  }
  queue_data->head = NULL;
  queue_data->tail = NULL;
}

void queue_node_destroy(queue_node_t * node) {
  if (node)
    free(node);
}

int64_t queue_node_get_element(queue_node_t * node) {
  return node->element;
}

int64_t queue_node_get_element_counter(queue_node_t * node) {
  return node->element_counter;
}

queue_node_t * queue_node_get_next(queue_node_t * node) {
  return node->next;
}
