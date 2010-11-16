/*
 *      The 1st-order linear-chain CRF with dyad features (CRF1d).
 *
 * Copyright (c) 2007-2010, Naoaki Okazaki
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the names of the authors nor the names of its contributors
 *       may be used to endorse or promote products derived from this
 *       software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* $Id$ */

#ifndef    __CRF1D_H__
#define    __CRF1D_H__

#include <crfsuite.h>
#include "crfsuite_internal.h"


/**
 * \defgroup crf1d_context.c
 */
/** @{ */

/**
 * Functionality flags for contexts.
 *  @see    crf1dc_new().
 */
enum {
    CTXF_BASE       = 0x01,
    CTXF_VITERBI    = 0x01,
    CTXF_MARGINALS  = 0x02,
    CTXF_ALL        = 0xFF,
};

/**
 * Reset flags.
 *  @see    crf1dc_reset().
 */
enum {
    RF_STATE    = 0x01,     /**< Reset state scores. */
    RF_TRANS    = 0x02,     /**< Reset transition scores. */
    RF_ALL      = 0xFF,     /**< Reset all. */
};

/**
 * Context structure.
 *  This structure maintains internal data for an instance.
 */
typedef struct {
    /**
     * Flag specifying the functionality.
     */
    int flag;

    /**
     * The total number of distinct labels (L).
     */
    int num_labels;

    /**
     * The number of items (T) in the instance.
     */
    int num_items;

    /**
     * The maximum number of labels.
     */
    int cap_items;

    /**
     * Logarithm of the normalization factor for the instance.
     *  This is equivalent to the total scores of all paths in the lattice.
     */
    floatval_t log_norm;

    /**
     * State scores.
     *  This is a [T][L] matrix whose element [t][l] presents total score
     *  of state features associating label #l at #t.
     */
    floatval_t *state;

    /**
     * Transition scores.
     *  This is a [L][L] matrix whose element [i][j] represents the total
     *  score of transition features associating labels #i and #j.
     */
    floatval_t *trans;

    /**
     * Alpha score matrix.
     *  This is a [T][L] matrix whose element [t][l] presents the total
     *  score of paths starting at BOS and arraiving at (t, l).
     */
    floatval_t *alpha_score;

    /**
     * Beta score matrix.
     *  This is a [T][L] matrix whose element [t][l] presents the total
     *  score of paths starting at (t, l) and arraiving at EOS.
     */
    floatval_t *beta_score;

    /**
     * Scale factor vector.
     *  This is a [T] vector whose element [t] presents the scaling
     *  coefficient for the alpha_score and beta_score.
     */
    floatval_t *scale_factor;

    /**
     * Row vector (work space).
     *  This is a [T] vector used internally for a work space.
     */
    floatval_t *row;

    /**
     * Label vector.
     *  This is a [T] vector whose element [t] stores the label at position #t.
     */
    int *labels;

    /**
     * Backward edges.
     *  This is a [T][L] matrix whose element [t][j] represents the label #i
     *  that yields the maximum score to arrive at (t, j).
     *  This member is available only with CTXF_VITERBI flag enabled.
     */
    int *backward_edge;

    /**
     * Exponents of state scores.
     *  This is a [T][L] matrix whose element [t][l] presents the exponent
     *  of the total score of state features associating label #l at #t.
     *  This member is available only with CTXF_MARGINALS flag.
     */
    floatval_t *exp_state;

    /**
     * Exponents of transition scores.
     *  This is a [L][L] matrix whose element [i][j] represents the exponent
     *  of the total score of transition features associating labels #i and #j.
     *  This member is available only with CTXF_MARGINALS flag.
     */
    floatval_t *exp_trans;

    /**
     * Model expectations of states.
     *  This is a [T][L] matrix whose element [t][l] presents the model
     *  expectation (marginal probability) of the state (t,l)
     *  This member is available only with CTXF_MARGINALS flag.
     */
    floatval_t *mexp_state;

    /**
     * Model expectations of transitions.
     *  This is a [L][L] matrix whose element [i][j] presents the model
     *  expectation of the transition (i--j).
     *  This member is available only with CTXF_MARGINALS flag.
     */
    floatval_t *mexp_trans;

} crf1d_context_t;

#define    MATRIX(p, xl, x, y)        ((p)[(xl) * (y) + (x)])

#define    ALPHA_SCORE(ctx, t) \
    (&MATRIX(ctx->alpha_score, ctx->num_labels, 0, t))
#define    BETA_SCORE(ctx, t) \
    (&MATRIX(ctx->beta_score, ctx->num_labels, 0, t))
#define    STATE_SCORE(ctx, i) \
    (&MATRIX(ctx->state, ctx->num_labels, 0, i))
#define    TRANS_SCORE(ctx, i) \
    (&MATRIX(ctx->trans, ctx->num_labels, 0, i))
#define    EXP_STATE_SCORE(ctx, i) \
    (&MATRIX(ctx->exp_state, ctx->num_labels, 0, i))
#define    EXP_TRANS_SCORE(ctx, i) \
    (&MATRIX(ctx->exp_trans, ctx->num_labels, 0, i))
#define    STATE_MEXP(ctx, i) \
    (&MATRIX(ctx->mexp_state, ctx->num_labels, 0, i))
#define    TRANS_MEXP(ctx, i) \
    (&MATRIX(ctx->mexp_trans, ctx->num_labels, 0, i))
#define    BACKWARD_EDGE_AT(ctx, t) \
    (&MATRIX(ctx->backward_edge, ctx->num_labels, 0, t))

crf1d_context_t* crf1dc_new(int flag, int L, int T);
int crf1dc_set_num_items(crf1d_context_t* ctx, int T);
void crf1dc_delete(crf1d_context_t* ctx);
void crf1dc_reset(crf1d_context_t* ctx, int flag);
void crf1dc_exp_state(crf1d_context_t* ctx);
void crf1dc_exp_transition(crf1d_context_t* ctx);
void crf1dc_alpha_score(crf1d_context_t* ctx);
void crf1dc_beta_score(crf1d_context_t* ctx);
void crf1dc_marginal(crf1d_context_t* ctx);
floatval_t crf1dc_score(crf1d_context_t* ctx, const int *labels);
floatval_t crf1dc_lognorm(crf1d_context_t* ctx);
floatval_t crf1dc_viterbi(crf1d_context_t* ctx);
void crf1dc_debug_context(FILE *fp);

/** @} */



/**
 * \defgroup crf1d_feature.c
 */
/** @{ */

/**
 * Feature type.
 */
enum {
    FT_STATE = 0,    /**< State features. */
    FT_TRANS,        /**< Transition features. */
};

/**
 * A feature (for either state or transition).
 */
typedef struct {
    /**
     * Feature type.
     *    Possible values are:
     *    - FT_STATE (0) for state features.
     *    - FT_TRANS (1) for transition features.
     */
    int        type;

    /**
     * Source id.
     *    The semantic of this field depends on the feature type:
     *    - attribute id for state features (type == 0).
     *    - output label id for transition features (type != 0).
     */
    int        src;

    /**
     * Destination id.
     *    Label id emitted by this feature.
     */
    int        dst;

    /**
     * Frequency (observation expectation).
     */
    floatval_t    freq;
} crf1df_feature_t;

/**
 * Feature references.
 *    This is a collection of feature ids used for faster accesses.
 */
typedef struct {
    int        num_features;    /**< Number of features referred */
    int*    fids;            /**< Array of feature ids */
} feature_refs_t;

crf1df_feature_t* crf1df_generate(
    int *ptr_num_features,
    const crf_instance_t *seqs,
    int num_sequences,
    int num_labels,
    int num_attributes,
    int holdout,
    int connect_all_attrs,
    int connect_all_edges,
    floatval_t minfreq,
    crf_logging_callback func,
    void *instance
    );

int crf1df_init_references(
    feature_refs_t **ptr_attributes,
    feature_refs_t **ptr_trans,
    const crf1df_feature_t *features,
    const int K,
    const int A,
    const int L
    );

/** @} */



/**
 * \defgroup crf1d_model.c
 */
/** @{ */

struct tag_crf1dm;
typedef struct tag_crf1dm crf1dm_t;

struct tag_crf1dmw;
typedef struct tag_crf1dmw crf1dmw_t;

typedef struct {
    int        type;
    int        src;
    int        dst;
    floatval_t weight;
} crf1dm_feature_t;

crf1dmw_t* crf1mmw(const char *filename);
int crf1dmw_close(crf1dmw_t* writer);
int crf1dmw_open_labels(crf1dmw_t* writer, int num_labels);
int crf1dmw_close_labels(crf1dmw_t* writer);
int crf1dmw_put_label(crf1dmw_t* writer, int lid, const char *value);
int crf1dmw_open_attrs(crf1dmw_t* writer, int num_attributes);
int crf1dmw_close_attrs(crf1dmw_t* writer);
int crf1dmw_put_attr(crf1dmw_t* writer, int aid, const char *value);
int crf1dmw_open_labelrefs(crf1dmw_t* writer, int num_labels);
int crf1dmw_close_labelrefs(crf1dmw_t* writer);
int crf1dmw_put_labelref(crf1dmw_t* writer, int lid, const feature_refs_t* ref, int *map);
int crf1dmw_open_attrrefs(crf1dmw_t* writer, int num_attrs);
int crf1dmw_close_attrrefs(crf1dmw_t* writer);
int crf1dmw_put_attrref(crf1dmw_t* writer, int aid, const feature_refs_t* ref, int *map);
int crf1dmw_open_features(crf1dmw_t* writer);
int crf1dmw_close_features(crf1dmw_t* writer);
int crf1dmw_put_feature(crf1dmw_t* writer, int fid, const crf1dm_feature_t* f);

crf1dm_t* crf1dm_new(const char *filename);
void crf1dm_close(crf1dm_t* model);
int crf1dm_get_num_attrs(crf1dm_t* model);
int crf1dm_get_num_labels(crf1dm_t* model);
const char *crf1dm_to_label(crf1dm_t* model, int lid);
int crf1dm_to_lid(crf1dm_t* model, const char *value);
int crf1dm_to_aid(crf1dm_t* model, const char *value);
const char *crf1dm_to_attr(crf1dm_t* model, int aid);
int crf1dm_get_labelref(crf1dm_t* model, int lid, feature_refs_t* ref);
int crf1dm_get_attrref(crf1dm_t* model, int aid, feature_refs_t* ref);
int crf1dm_get_featureid(feature_refs_t* ref, int i);
int crf1dm_get_feature(crf1dm_t* model, int fid, crf1dm_feature_t* f);
void crf1dm_dump(crf1dm_t* model, FILE *fp);

/** @} */



/**
 * \defgroup crf1d_tag.c
 */
/** @{ */

struct tag_crf1mt;
typedef struct tag_crf1mt crf1dt_t;

crf1dt_t *crf1dt_new(crf1dm_t* crf1dm);
void crf1dt_delete(crf1dt_t* crf1dt);
int crf1dt_tag(crf1dt_t* crf1dt, crf_instance_t *inst, int* output, floatval_t *ptr_score);

/** @} */


/**
 * \defgroup crf1d_learn.c
 */
/** @{ */

crf_train_data_t *crf1dl_create_instance_batch();

/** @} */


/*
typedef struct {
    floatval_t  sigma;
    floatval_t  lambda;
    floatval_t  t0;
    int         max_iterations;
    int         period;
    floatval_t  delta;
    floatval_t  calibration_eta;
    floatval_t  calibration_rate;
    int         calibration_samples;
    int         calibration_candidates;
} crf1dl_sgd_option_t;

void crf1dl_shuffle(int *perm, int N, int init);

int crf1dl_sgd(crf1dl_t* crf1dt, crf1dl_option_t *opt);
int crf1dl_sgd_options(crf_params_t* params, crf1dl_option_t* opt, int mode);
*/


/* crf1m_tag.c */



#endif/*__CRF1D_H__*/
