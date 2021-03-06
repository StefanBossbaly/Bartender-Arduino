/**
 * @file   error.h
 * @brief  Defines the errors codes that functions can return.
 * @author Stefan Bossbaly (sbossb@gmail.com)
 * @date   April, 2014
 *
 * This file contains definitions for all the error codes that can
 * be return from functions. The documentation will specify when a
 * function returns an
 error code. Note that the maximum size of an error
 * code is 1 byte so a uint8_t data type is optimal for storing an error
 * code.
 *
 * Here is an example on how you handle a function returning an error
 * code.
 *
 * @code
 * if (uint8_t error = example_function(param1, param2) != E_NO_ERROR)
 * {
 *		// error contains an error definition
 * }
 * @endcode
 */
#ifndef ERROR_H_
#define ERROR_H_

/**
 * The no error code. If an error did not occur this code is returned.
 */
#define E_NO_ERROR 0x00

/**
 * The general error code. Try to avoid using this code and return a more
 * specific error code.
 */
#define E_GENERAL 0x01

/**
 * The overflow error code. Returned if the requested function would cause an
 * overflow.
 */
#define E_BUFF_OVERFLOW 0x02

/**
 * The empty error code. Returned if the the function can not be performed on
 * an empty data structure.
 */
#define E_EMPTY 0x03

/**
 * The busy error code. Returned if the function can not be performed because
 * it is busy doing something else.
 */
#define E_BUSY 0x04

/**
 * The interrupted error code. Returned if the function was interrupted and
 * the interrupt effects the logic of the function so that is does not fully
 * complete.
 */
#define E_INT 0x05

/**
 * The invalid function call error code. Returned if the function called did not
 * have a precondition met.
 */
#define E_INV_CALL 0x06

#endif /* ERROR_H_ */
