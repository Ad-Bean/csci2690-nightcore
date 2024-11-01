#pragma once

#include "base/common.h"
#include "common/protocol.h"
#include "common/stat.h"
#include "common/uv.h"
#include "server/connection_base.h"
#include "server/io_worker.h"
#include "utils/appendable_buffer.h"

namespace faas {
  namespace gateway {

    class Server;

    // EngineConnection class handles the connection between the server and the engine.
    class EngineConnection final : public server::ConnectionBase {
     public:
      // Base type ID for the connection.
      static constexpr int kBaseTypeId = 2;

      // Returns the type ID based on the node ID.
      static int type_id(uint16_t node_id) { return kBaseTypeId + node_id; }

      // Constructor for EngineConnection.
      // @param server: Pointer to the server instance.
      // @param node_id: ID of the node.
      // @param conn_id: ID of the connection.
      // @param initial_data: Initial data for the connection.
      EngineConnection(Server* server, uint16_t node_id, uint16_t conn_id, std::span<const char> initial_data);

      // Destructor for EngineConnection.
      ~EngineConnection();

      // Returns the node ID.
      uint16_t node_id() const { return node_id_; }

      // Returns the connection ID.
      uint16_t conn_id() const { return conn_id_; }

      // Initializes the UV handle.
      // @param uv_loop: Pointer to the UV loop.
      // @return: Pointer to the UV stream.
      uv_stream_t* InitUVHandle(uv_loop_t* uv_loop) override;

      // Starts the connection.
      // @param io_worker: Pointer to the IO worker.
      void Start(server::IOWorker* io_worker) override;

      // Schedules the connection to close.
      void ScheduleClose() override;

      // Sends a message through the connection.
      // @param message: The message to send.
      // @param payload: The payload of the message.
      void SendMessage(const protocol::GatewayMessage& message, std::span<const char> payload);

     private:
      // Enum representing the state of the connection.
      enum State { kCreated, kRunning, kClosing, kClosed };

      Server* server_;               // Pointer to the server instance.
      uint16_t node_id_;             // ID of the node.
      uint16_t conn_id_;             // ID of the connection.
      server::IOWorker* io_worker_;  // Pointer to the IO worker.
      State state_;                  // Current state of the connection.
      uv_tcp_t uv_tcp_handle_;       // UV TCP handle.

      std::string log_header_;  // Log header for the connection.

      utils::AppendableBuffer read_buffer_;  // Buffer for reading data.

      // Processes gateway messages.
      void ProcessGatewayMessages();

      // UV callback for buffer allocation.
      DECLARE_UV_ALLOC_CB_FOR_CLASS(BufferAlloc);

      // UV callback for receiving data.
      DECLARE_UV_READ_CB_FOR_CLASS(RecvData);

      // UV callback for data sent.
      DECLARE_UV_WRITE_CB_FOR_CLASS(DataSent);

      // UV callback for closing the connection.
      DECLARE_UV_CLOSE_CB_FOR_CLASS(Close);

      // Disallows copy and assignment.
      DISALLOW_COPY_AND_ASSIGN(EngineConnection);
    };

  }  // namespace gateway
}  // namespace faas
