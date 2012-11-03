/************************************************************************/
/*! \class RtError
    \brief Exception handling class for RtAudio & RtMidi.

    The RtError class is quite simple but it does allow errors to be
    "caught" by RtError::Type. See the RtAudio and RtMidi
    documentation to know which methods can throw an RtError.

*/
/************************************************************************/

#ifndef RTERROR_H
#define RTERROR_H

#include <exception>
#include <iostream>
#include <string>

/**
 * @brief
 *
 */
class RtError : public std::exception
{
 public:
  //! Defined RtError types.
  /**
   * @brief
   *
   */
  enum Type {
    WARNING,           /*!< A non-critical error. */
    DEBUG_WARNING,     /*!< A non-critical error which might be useful for debugging. */
    UNSPECIFIED,       /*!< The default, unspecified error type. */
    NO_DEVICES_FOUND,  /*!< No devices found on system. */
    INVALID_DEVICE,    /*!< An invalid device ID was specified. */
    MEMORY_ERROR,      /*!< An error occured during memory allocation. */
    INVALID_PARAMETER, /*!< An invalid parameter was specified to a function. */
    INVALID_USE,       /*!< The function was called incorrectly. */
    DRIVER_ERROR,      /*!< A system driver error occured. */
    SYSTEM_ERROR,      /*!< A system error occured. */
    THREAD_ERROR       /*!< A thread error occured. */
  };

  //! The constructor.
/**
 * @brief
 *
 * @param message
 * @param type
 */
  RtError( const std::string& message, Type type = RtError::UNSPECIFIED ) throw() : message_(message), type_(type) {}
 
  //! The destructor.
  /**
   * @brief
   *
   */
  virtual ~RtError( void ) throw() {}

  //! Prints thrown error message to stderr.
  /**
   * @brief
   *
   */
  virtual void printMessage( void ) throw() { std::cerr << '\n' << message_ << "\n\n"; }

  //! Returns the thrown error message type.
  /**
   * @brief
   *
   * @return const Type
   */
  virtual const Type& getType(void) throw() { return type_; }

  //! Returns the thrown error message string.
  /**
   * @brief
   *
   * @return const std::string
   */
  virtual const std::string& getMessage(void) throw() { return message_; }

  //! Returns the thrown error message as a c-style string.
  /**
   * @brief
   *
   * @return const char
   */
  virtual const char* what( void ) const throw() { return message_.c_str(); }

 protected:
  std::string message_; /**< TODO */
  Type type_; /**< TODO */
};

#endif
