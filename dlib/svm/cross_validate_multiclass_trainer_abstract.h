// Copyright (C) 2010  Davis E. King (davis@dlib.net)
// License: Boost Software License   See LICENSE.txt for the full license.
#undef DLIB_CROSS_VALIDATE_MULTICLASS_TRaINER_ABSTRACT_H__
#ifdef DLIB_CROSS_VALIDATE_MULTICLASS_TRaINER_ABSTRACT_H__

#include <vector>
#include "../matrix.h"

namespace dlib
{

// ----------------------------------------------------------------------------------------

    template <
        typename dec_funct_type,
        typename sample_type,
        typename label_type
        >
    const matrix<typename dec_funct_type::scalar_type, 0, 0, typename dec_funct_type::mem_manager_type> 
    test_multiclass_decision_function (
        const dec_funct_type& dec_funct,
        const std::vector<sample_type>& x_test,
        const std::vector<label_type>& y_test
    );
    /*!
        requires
            - is_learning_problem(x_test, y_test)
            - dec_funct_type == some kind of multiclass decision function object 
              (e.g. one_vs_one_decision_function)
        ensures
            - Tests dec_funct against the given samples in x_test and labels in y_test
              and returns a confusion matrix summarizing the results.
            - let L = dec_funct.get_labels().  Then the confusion matrix C returned 
              by this function has the following properties.
                - C.nr() == C.nc() == L.size()
                - C(r,c) == the number of times a sample with label L(r) was predicted
                  to have a label of L(c)
            - Any samples with a y_test value not in L are ignored.  That is, samples
              with labels the decision function hasn't ever seen before are ignored.
    !*/

// ----------------------------------------------------------------------------------------

    template <
        typename trainer_type,
        typename sample_type,
        typename label_type 
        >
    const matrix<typename trainer_type::scalar_type, 0, 0, typename trainer_type::mem_manager_type> 
    cross_validate_multiclass_trainer (
        const trainer_type& trainer,
        const std::vector<sample_type>& x,
        const std::vector<label_type>& y,
        const long folds
    );
    /*!
        requires
            - is_learning_problem(x,y)
            - 1 < folds <= x.size()
            - trainer_type == some kind of multiclass classification trainer object (e.g. one_vs_one_trainer)
        ensures
            - performs k-fold cross validation by using the given trainer to solve the
              given multiclass classification problem for the given number of folds.
              Each fold is tested using the output of the trainer and the confusion
              matrix from all folds is summed and returned.
            - The total confusion matrix is computed by running test_binary_decision_function()
              on each fold and summing its output.
            - The number of folds used is given by the folds argument.
            - let L = select_all_distinct_labels(y).  Then the confusion matrix C returned 
              by this function has the following properties.
                - C.nr() == C.nc() == L.size()
                - C(r,c) == the number of times a sample with label L(r) was predicted
                  to have a label of L(c)
    !*/

}

// ----------------------------------------------------------------------------------------

#endif // DLIB_CROSS_VALIDATE_MULTICLASS_TRaINER_ABSTRACT_H__


