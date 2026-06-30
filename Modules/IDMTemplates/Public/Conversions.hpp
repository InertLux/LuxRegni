/* IDM Conversions Library
 * 
 * Provides type-safe SQLite value extraction and binding for C++ objects.
 * Handles compile-time parameter pack iteration and runtime SQLite conversions.
 * 
 * SUPPORTED TYPES:
 *   - int           (32-bit signed integer)
 *   - int64_t       (64-bit signed integer)
 *   - float         (32-bit floating-point)
 *   - double        (64-bit floating-point)
 *   - std::string   (UTF-8 text)
 * 
 * 
 * CALL STACK ROUTING:
 *   
 *   IMPORT TO TYPE
 *   Load Path (Database -> Object):
 *     DataTypeImpl::LoadImpl()
 *       -> BindColumnsToObjectImpl() [fold expression over Properties]
 *         -> ExtractAndBind<Prop>() [per-property]
 *           -> ExtractColumnValue<ValueType>() [type specialization]
 *             -> sqlite3_column_*() [SQLite C API]
 *   
 * 
 *   EXPORT TO TYPE
 *   Save Path (Object -> Database):
 *     DataTypeImpl::SaveImpl()
 *       -> BindMembersToStatementImpl() [fold expression over Properties]
 *         -> BindMemberValue<Prop>() [per-property]
 *           -> BindValue<ValueType>() [type specialization]
 *             -> sqlite3_bind_*() [SQLite C API]
 *   
 * 
 * 
    NEW TYPE:
================================================

template<>
inline bool ExtractColumnValue<bool>(sqlite3_stmt* stmt, int col) {
    return sqlite3_column_int(stmt, col) != 0;
}



template<>
inline void BindValue<bool>(sqlite3_stmt* stmt, int idx, const bool& val) {
    sqlite3_bind_int(stmt, idx, val ? 1 : 0);
}

================================================
 * 
 */

#pragma once

#include <sqlite3.h>
#include <string>
#include <type_traits>

namespace IDMConversions {
    
    // ========== Index Sequence for Compile-Time Iteration ==========
    // Holds a compile-time sequence of indices for parameter pack expansion.
    template<size_t... Is>
    struct IndexSequence {};
    
    // Generates an IndexSequence containing [0, N-1] at compile-time.
    template<size_t N, size_t... Is>
    struct MakeIndexSequence : MakeIndexSequence<N - 1, N - 1, Is...> {};
    
    template<size_t... Is>
    struct MakeIndexSequence<0, Is...> { 
        using type = IndexSequence<Is...>; 
    };
    
    template<size_t N>
    using make_index_sequence = typename MakeIndexSequence<N>::type;
    
    // ========== SQLite Column Value Extraction ==========
    // Generic template for extracting typed values from SQLite result columns.
    template<typename T>
    T ExtractColumnValue(sqlite3_stmt* stmt, int col);
    
    // Extract 32-bit signed integer.
    template<>
    inline int ExtractColumnValue<int>(sqlite3_stmt* stmt, int col) {
        return sqlite3_column_int(stmt, col);
    }
    
    // Extract text; returns empty string on NULL.
    template<>
    inline std::string ExtractColumnValue<std::string>(sqlite3_stmt* stmt, int col) {
        const unsigned char* text = sqlite3_column_text(stmt, col);
        if (!text) return std::string();
        return std::string(reinterpret_cast<const char*>(text));
    }
    
    // Extract 64-bit floating-point value.
    template<>
    inline double ExtractColumnValue<double>(sqlite3_stmt* stmt, int col) {
        return sqlite3_column_double(stmt, col);
    }
    
    // Extract 32-bit float; cast from REAL (double).
    template<>
    inline float ExtractColumnValue<float>(sqlite3_stmt* stmt, int col) {
        return static_cast<float>(sqlite3_column_double(stmt, col));
    }
    
    // Extract 64-bit signed integer.
    template<>
    inline int64_t ExtractColumnValue<int64_t>(sqlite3_stmt* stmt, int col) {
        return sqlite3_column_int64(stmt, col);
    }
    
    // ========== SQLite Parameter Binding ==========
    // Generic template for binding typed values to SQLite prepared statement parameters.
    template<typename T>
    void BindValue(sqlite3_stmt* stmt, int idx, const T& val);
    
    // Bind 32-bit signed integer.
    template<>
    inline void BindValue<int>(sqlite3_stmt* stmt, int idx, const int& val) {
        sqlite3_bind_int(stmt, idx, val);
    }
    
    // Bind text string (SQLITE_TRANSIENT tells SQLite to copy the data).
    template<>
    inline void BindValue<std::string>(sqlite3_stmt* stmt, int idx, const std::string& val) {
        sqlite3_bind_text(stmt, idx, val.c_str(), -1, SQLITE_TRANSIENT);
    }
    
    // Bind 64-bit floating-point value.
    template<>
    inline void BindValue<double>(sqlite3_stmt* stmt, int idx, const double& val) {
        sqlite3_bind_double(stmt, idx, val);
    }
    
    // Bind 32-bit float; cast to double for storage.
    template<>
    inline void BindValue<float>(sqlite3_stmt* stmt, int idx, const float& val) {
        sqlite3_bind_double(stmt, idx, static_cast<double>(val));
    }
    
    // Bind 64-bit signed integer.
    template<>
    inline void BindValue<int64_t>(sqlite3_stmt* stmt, int idx, const int64_t& val) {
        sqlite3_bind_int64(stmt, idx, val);
    }

    // Extract boolean; non-zero SQLite int is true.
template<>
inline bool ExtractColumnValue<bool>(sqlite3_stmt* stmt, int col) {
    return sqlite3_column_int(stmt, col) != 0;
}

// Bind boolean as 0 or 1.
template<>
inline void BindValue<bool>(sqlite3_stmt* stmt, int idx, const bool& val) {
    sqlite3_bind_int(stmt, idx, val ? 1 : 0);
}
    

template<>
inline unsigned long ExtractColumnValue<unsigned long>(sqlite3_stmt* stmt, int col) {
    return static_cast<unsigned long>(sqlite3_column_int64(stmt, col));
}

template<>
inline void BindValue<unsigned long>(sqlite3_stmt* stmt, int idx, const unsigned long& val) {
    sqlite3_bind_int64(stmt, idx, static_cast<int64_t>(val));
}



} // namespace IDMConversions
