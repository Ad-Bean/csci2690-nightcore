#pragma once

#include "base/common.h"
#include "ipc/base.h"

namespace faas {
  namespace ipc {

    class ShmRegion;

    // ShmCreate creates a shared memory region with the given name and size.
    // Returns nullptr on failure.
    std::unique_ptr<ShmRegion> ShmCreate(std::string_view name, size_t size);

    // ShmOpen opens an existing shared memory region with the given name.
    // If readonly is true, the region is opened in read-only mode.
    // Returns nullptr on failure.
    std::unique_ptr<ShmRegion> ShmOpen(std::string_view name, bool readonly = true);

    class ShmRegion {
     public:
      // Destructor for ShmRegion
      ~ShmRegion();

      // Enables the removal of the shared memory region upon destruction
      void EnableRemoveOnDestruction() { remove_on_destruction_ = true; }

      // Disables the removal of the shared memory region upon destruction
      void DisableRemoveOnDestruction() { remove_on_destruction_ = false; }

      // Returns a pointer to the base address of the shared memory region
      char* base() { return base_; }

      // Returns a const pointer to the base address of the shared memory region
      const char* base() const { return base_; }

      // Returns the size of the shared memory region
      size_t size() const { return size_; }

      // Returns a std::span representing the shared memory region
      std::span<const char> to_span() const { return std::span<const char>(base_, size_); }

     private:
      // Constructor for ShmRegion
      ShmRegion(std::string_view name, char* base, size_t size)
          : name_(name), base_(base), size_(size), remove_on_destruction_(false) {}

      // Name of the shared memory region
      std::string name_;

      // Base address of the shared memory region
      char* base_;

      // Size of the shared memory region
      size_t size_;

      // Flag indicating whether to remove the shared memory region upon destruction
      bool remove_on_destruction_;

      // Friend declarations to allow ShmCreate and ShmOpen to access private members
      friend std::unique_ptr<ShmRegion> ShmCreate(std::string_view name, size_t size);
      friend std::unique_ptr<ShmRegion> ShmOpen(std::string_view name, bool readonly);

      // Macro to disallow copy and assignment
      DISALLOW_COPY_AND_ASSIGN(ShmRegion);
    };

  }  // namespace ipc
}  // namespace faas
