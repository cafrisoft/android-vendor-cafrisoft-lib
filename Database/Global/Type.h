#ifndef DATABASE_TYPE_H__
#define DATABASE_TYPE_H__

#ifdef __cplusplus

namespace Database {
    namespace SqlType {

        enum class Join {
            Unknown = -1, 
            Inner = 0,
            Left,
            Right
        };

    };  // namespace VarType

}; // namespace Comm

#endif  // __cplusplus

#endif
