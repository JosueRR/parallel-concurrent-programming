/*
 * Copyright 2021 Josue Retana  - UCR
 * Header file of a dynamic container of type queue to store the factoring of each number
 * It has the special feature of storing a queue in each node to store the result of the factorization process
 */
#ifndef TAREAS_PRIMEFACT_OMP_MPI_SRC_QUEUE_DATA_H_
#define TAREAS_PRIMEFACT_OMP_MPI_SRC_QUEUE_DATA_H_
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

/** @struct queue_node
 *  @brief Nodes of the queue which contains the values and their prime factorization
 * @code
  typedef struct queue_node {
    int64_t element;
    queue_node_t * next;
    int64_t element_counter;
    queue_data_t primefact;
    int invalid_number;
  }queue_node_t;
 * @endcode

 *  @var queue_node::element 
 *  Member 'element' is the positive 64 bits value read from the input stream
 * 
 *  @var queue_node::element_counter 
 *  Member 'element_counter' counts how many times is repetead the element in the queue
 *   is used to know the exponente of the prime factors
 */
typedef struct queue_node queue_node_t;

/** @struct queue_data
 * @brief struct to store a pointer to the head and tail of the queue
 * @code
  typedef struct queue_data {
    queue_node_t * head;
    queue_node_t * tail;
    int64_t size;
  }queue_data_t;
 * @endcode
 * @var queue_data::head 
 * Member 'head' points to the first node of the queue
 * 
 * @var queue_data::head 
 * Member 'head' points to the last node of the queue
 *
 * @var queue_data::size 
 * Member 'size' indicates the number of nodes in the queue
 * 
 */
typedef struct queue_data {
  queue_node_t * head;
  queue_node_t * tail;
  uint64_t size;
}queue_data_t;

/** @brief queue initializer
 * @details This methods sets to 0 all the attributes
 * @param queue_data pointer to register where methods will run
 * @remark *IMPORTANT* this method doesn't allocate any memory
 */
void queue_data_init(queue_data_t * queue_data);

/** @brief Method to append a new value to the end of the queue
 * @param queue_data pointer to register where methods will run
 * @param value that will be added to que queue
 * @return Returns 1 if there was an error trying to allocate memory
 * @remark invalid parameter is set to one, when a string of characters is read from the input stream or is a out of range value
 */
int queue_data_append(queue_data_t * queue_data, int64_t value);

/** @brief This is used to add a ne value to the queue if it is no repeated
 * @details If the value is already in the queue, the element_counter attirbute is incremented by one
 * @param queue pointer to register where methods will run
 * @param value integer of 64 bits that will be added to que queue
 * @return Returns 1 if there was an error trying to allocate memory
 * @remark This is used by class calculator to store the factors exponent
 */
int queue_data_insert(queue_data_t * queue, int64_t value);

/** @brief Method to search a given value in the queue
 * @param current_queue pointer to register where methods will run
 * @param search_value integer of 64 bits that we are searching
 * @remark If the value is found a pinter to the node is returne, if not a null is returned
 */
queue_node_t * queue_data_search(queue_data_t * current_queue,
 int64_t search_value);

/** @brief Destructor of the class
 * @param queue_data pointer to queue that will be destroyed
 * @details This method allows us to free the memory allocated before
 * @remark Each node is destroyed one by one
 */
void queue_data_destroy(queue_data_t * queue_data);

/** @brief Destructor of the nodes
 * @param node pointer to node that will be destroyed
 * @details This method allows us to free the memory allocated
 * @remark All the attributes are destroyed even if it is another queue
 */
void queue_node_destroy(queue_node_t * node);

/** @brief Method that gives us access to the node element
 * @param node to the actual node
 * @return A copy of the actual element
 */
int64_t queue_node_get_element(queue_node_t * node);

/** @brief Method that gives us access to the element counter
 * @param node to the actual node
 * @return A copy of the element counter
 */
int64_t queue_node_get_element_counter(queue_node_t * node);

/** @brief Method that gives us access to the next node
 * @param node to the actual node
 * @return A pointer to the next node
 */
queue_node_t * queue_node_get_next(queue_node_t * node);

#endif  // TAREAS_PRIMEFACT_OMP_MPI_SRC_QUEUE_DATA_H_
