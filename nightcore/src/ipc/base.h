#pragma once

#include "base/common.h"

namespace faas {
  namespace ipc {
    /**
     * Sets the root path for IPC and optionally creates the necessary directories.
     * 
     * @param path The root path to set.
     * @param create If true, creates the directories; otherwise, checks if they exist.
     */
    void SetRootPathForIpc(std::string_view path, bool create = false);

    /**
     * Gets the root path for IPC.
     * 
     * @return The root path for IPC.
     */
    std::string_view GetRootPathForIpc();

    /**
     * Gets the path for the engine Unix socket.
     * 
     * @return The path for the engine Unix socket.
     */
    std::string_view GetEngineUnixSocketPath();

    /**
     * Gets the root path for shared memory.
     * 
     * @return The root path for shared memory.
     */
    std::string_view GetRootPathForShm();

    /**
     * Gets the root path for FIFO.
     * 
     * @return The root path for FIFO.
     */
    std::string_view GetRootPathForFifo();

    /**
     * Gets the input FIFO name for a function worker.
     * 
     * @param client_id The client ID of the function worker.
     * @return The input FIFO name for the function worker.
     */
    std::string GetFuncWorkerInputFifoName(uint16_t client_id);

    /**
     * Gets the output FIFO name for a function worker.
     * 
     * @param client_id The client ID of the function worker.
     * @return The output FIFO name for the function worker.
     */
    std::string GetFuncWorkerOutputFifoName(uint16_t client_id);

    /**
     * Gets the input shared memory name for a function call.
     * 
     * @param full_call_id The full call ID of the function call.
     * @return The input shared memory name for the function call.
     */
    std::string GetFuncCallInputShmName(uint64_t full_call_id);

    /**
     * Gets the output shared memory name for a function call.
     * 
     * @param full_call_id The full call ID of the function call.
     * @return The output shared memory name for the function call.
     */
    std::string GetFuncCallOutputShmName(uint64_t full_call_id);

    /**
     * Gets the output FIFO name for a function call.
     * 
     * @param full_call_id The full call ID of the function call.
     * @return The output FIFO name for the function call.
     */
    std::string GetFuncCallOutputFifoName(uint64_t full_call_id);

  }  // namespace ipc
}  // namespace faas
