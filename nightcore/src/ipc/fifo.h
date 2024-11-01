#pragma once

#include "base/common.h"

namespace faas {
  namespace ipc {

    /**
     * @brief Creates a FIFO (named pipe) with the given name.
     * 
     * @param name The name of the FIFO to create.
     * @return true if the FIFO was successfully created, false otherwise.
     */
    bool FifoCreate(std::string_view name);

    /**
     * @brief Removes the FIFO with the given name.
     * 
     * @param name The name of the FIFO to remove.
     */
    void FifoRemove(std::string_view name);

    /**
     * @brief Opens the FIFO for reading.
     * 
     * @param name The name of the FIFO to open.
     * @param nonblocking If true, the FIFO is opened in non-blocking mode. Default is true.
     * @return The file descriptor of the opened FIFO, or -1 on failure.
     */
    int FifoOpenForRead(std::string_view name, bool nonblocking = true);

    /**
     * @brief Opens the FIFO for writing.
     * 
     * @param name The name of the FIFO to open.
     * @param nonblocking If true, the FIFO is opened in non-blocking mode. Default is true.
     * @return The file descriptor of the opened FIFO, or -1 on failure.
     */
    int FifoOpenForWrite(std::string_view name, bool nonblocking = true);

    /**
     * @brief Opens the FIFO for both reading and writing.
     * 
     * @param name The name of the FIFO to open.
     * @param nonblocking If true, the FIFO is opened in non-blocking mode. Default is true.
     * @return The file descriptor of the opened FIFO, or -1 on failure.
     */
    int FifoOpenForReadWrite(std::string_view name, bool nonblocking = true);

    /**
     * @brief Unsets the non-blocking mode on the given file descriptor.
     * 
     * @param fd The file descriptor to modify.
     */
    void FifoUnsetNonblocking(int fd);

    /**
     * @brief Polls the FIFO for readability.
     * 
     * @param fd The file descriptor of the FIFO to poll.
     * @param timeout_ms The timeout in milliseconds. Default is -1 (infinite timeout).
     * @return true if the FIFO is readable, false otherwise.
     */
    bool FifoPollForRead(int fd, int timeout_ms = -1);

  }  // namespace ipc
}  // namespace faas
