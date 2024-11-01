#pragma once

#include "base/common.h"
#include "base/thread.h"
#include "common/func_config.h"
#include "common/protocol.h"
#include "common/stat.h"
#include "common/uv.h"
#include "launcher/engine_connection.h"
#include "launcher/func_process.h"
#include "utils/buffer_pool.h"

namespace faas {
  namespace launcher {

    // Launcher class inherits from uv::Base and manages the lifecycle of function processes.
    class Launcher : public uv::Base {
     public:
      // Buffer size for reading and writing data.
      static constexpr size_t kBufferSize = 4096;
      // Ensure the buffer size is sufficient for protocol messages.
      static_assert(sizeof(protocol::Message) <= kBufferSize, "kBufferSize is too small");

      // Enumeration for different function process modes.
      enum Mode { kInvalidMode = 0, kCppMode = 1, kGoMode = 2, kNodeJsMode = 3, kPythonMode = 4 };

      // Constructor for Launcher.
      Launcher();
      // Destructor for Launcher.
      ~Launcher();

      // Set the function ID.
      void set_func_id(int func_id) { func_id_ = func_id; }
      // Set the function process name.
      void set_fprocess(std::string_view fprocess) { fprocess_ = std::string(fprocess); }
      // Set the working directory for the function process.
      void set_fprocess_working_dir(std::string_view path) { fprocess_working_dir_ = std::string(path); }
      // Set the output directory for the function process.
      void set_fprocess_output_dir(std::string_view path) { fprocess_output_dir_ = std::string(path); }
      // Set the mode for the function process.
      void set_fprocess_mode(Mode mode) { fprocess_mode_ = mode; }
      // Set the TCP port for the engine connection.
      void set_engine_tcp_port(int port) { engine_tcp_port_ = port; }

      // Get the function ID.
      int func_id() const { return func_id_; }
      // Get the function process name.
      std::string_view fprocess() const { return fprocess_; }
      // Get the working directory for the function process.
      std::string_view fprocess_working_dir() const { return fprocess_working_dir_; }
      // Get the output directory for the function process.
      std::string_view fprocess_output_dir() const { return fprocess_output_dir_; }
      // Get the TCP port for the engine connection.
      int engine_tcp_port() const { return engine_tcp_port_; }

      // Get the function name from the function configuration.
      std::string_view func_name() const {
        const FuncConfig::Entry* entry = func_config_.find_by_func_id(func_id_);
        return entry->func_name;
      }
      // Get the function configuration in JSON format.
      std::string_view func_config_json() const { return func_config_json_; }
      // Check if the function worker uses the engine socket.
      bool func_worker_use_engine_socket() const { return func_worker_use_engine_socket_; }

      // Start the launcher.
      void Start();
      // Schedule the launcher to stop.
      void ScheduleStop();
      // Wait for the launcher to finish.
      void WaitForFinish();

      // Allocate a new read buffer.
      void NewReadBuffer(size_t suggested_size, uv_buf_t* buf);
      // Return a read buffer.
      void ReturnReadBuffer(const uv_buf_t* buf);
      // Allocate a new write buffer.
      void NewWriteBuffer(uv_buf_t* buf);
      // Return a write buffer.
      void ReturnWriteBuffer(char* buf);
      // Allocate a new write request.
      uv_write_t* NewWriteRequest();
      // Return a write request.
      void ReturnWriteRequest(uv_write_t* write_req);

      // Handle engine connection close event.
      void OnEngineConnectionClose();
      // Handle function process exit event.
      void OnFuncProcessExit(FuncProcess* func_process);
      // Handle receiving handshake response.
      bool OnRecvHandshakeResponse(const protocol::Message& handshake_response, std::span<const char> payload);
      // Handle receiving a message.
      void OnRecvMessage(const protocol::Message& message);

     private:
      // Enumeration for the state of the launcher.
      enum State { kCreated, kRunning, kStopping, kStopped };
      // Atomic variable to store the state of the launcher.
      std::atomic<State> state_;

      // Function ID.
      int func_id_;
      // Function process name.
      std::string fprocess_;
      // Working directory for the function process.
      std::string fprocess_working_dir_;
      // Output directory for the function process.
      std::string fprocess_output_dir_;
      // Mode for the function process.
      Mode fprocess_mode_;
      // TCP port for the engine connection.
      int engine_tcp_port_;

      // UV loop for handling events.
      uv_loop_t uv_loop_;
      // UV async handle for stop event.
      uv_async_t stop_event_;
      // Thread for running the event loop.
      base::Thread event_loop_thread_;
      // Buffer pool for managing buffers.
      utils::BufferPool buffer_pool_;
      // Object pool for managing write requests.
      utils::SimpleObjectPool<uv_write_t> write_req_pool_;

      // Function configuration.
      FuncConfig func_config_;
      // Function configuration in JSON format.
      std::string func_config_json_;
      // Flag to indicate if the function worker uses the engine socket.
      bool func_worker_use_engine_socket_;
      // Engine connection instance.
      EngineConnection engine_connection_;
      // Vector of unique pointers to function processes.
      std::vector<std::unique_ptr<FuncProcess>> func_processes_;

      // Statistics collector for engine message delay.
      stat::StatisticsCollector<int32_t> engine_message_delay_stat_;

      // Main function for the event loop thread.
      void EventLoopThreadMain();

      // Declare UV async callback for stop event.
      DECLARE_UV_ASYNC_CB_FOR_CLASS(Stop);

      // Disallow copy and assign for Launcher.
      DISALLOW_COPY_AND_ASSIGN(Launcher);
    };

  }  // namespace launcher
}  // namespace faas
