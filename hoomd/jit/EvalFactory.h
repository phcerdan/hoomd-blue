#pragma once

// do not include python headers
#define HOOMD_NOPYTHON
#include "hoomd/HOOMDMath.h"
#include "hoomd/VectorMath.h"

#include "OrcLazyJIT.h"

class EvalFactory
    {
    public:
        typedef float (*EvalFnPtr)(const vec3<float>& r_ij, unsigned int type_i, const quat<float>& q_i, unsigned int type_j, const quat<float>& q_j);

        //! Constructor
        EvalFactory(const std::string& llvm_ir);

        //! Return the evaluator
        EvalFnPtr getEval()
            {
            return m_eval;
            }

        //! Get the error message from initialization
        const std::string& getError()
            {
            return m_error_msg;
            }

    private:
        std::shared_ptr<llvm::OrcLazyJIT> m_jit; //!< The persistent JIT engine
        EvalFnPtr m_eval;         //!< Function pointer to evaluator

        std::string m_error_msg; //!< The error message if initialization fails
    };
