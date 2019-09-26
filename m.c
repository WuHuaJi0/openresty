#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

typedef struct {
    ngx_str_t output_words;
} ngx_http_mytest_loc_conf_t;

typedef struct {
    /* todo: ngx_conf_t */
    ngx_int_t (*preconfiguration)(ngx_conf_t *cf);
    ngx_int_t (*postconfiguration)(ngx_conf_t *cf);

    void *(*create_main_conf)(ngx_conf_t *cf);
    void *(*init_main_conf)(ngx_conf_t *cf, void *conf);

    void *(*create_srv_conf)(ngx_conf_t *cf);
    void *(*merge_srv_conf)(ngx_conf_t *cf, void *prev , void *conf);

    void *(*create_loc_conf)(ngx_conf_t *cf);
    void *(*merge_loc_conf)(ngx_conf_t *cf, void *prev , void *conf);
} ngx_http_module_t;


//todo
static void* ngx_http_mytest_create_loc_conf(ngx_conf_t *cf) {
    ngx_http_mytest_loc_conf_t *conf;
}

//todo
static char* ngx_http_mytest_merge_loc_conf (ngx_conf_t *cf,void *parent, void *child){

}

static ngx_http_module_t ngx_http_mytest_module_ctx = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ngx_http_mytest_create_loc_conf,
    ngx_http_mytest_merge_loc_conf,
};

struct ngx_command_s {
    ngx_str_t name;
    ngx_unit_t type;
    char *(*set)(ngx_conf_t *cf, ngx_command_t *cmd , void *conf);
    ngx_uint_t conf;
    ngx_unit offset;
    void *post;
};


static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t *r){

}


static char* ngx_http_mytest(ngx_conf_t *cf,ngx_command_t *cmd, void* conf){

    /*todo:
     * ngx_conf_t : name, args, cycle ,pool,
     * ngx_http_core_loc_conf_t :
     * ngx_http_conf_get_module_loc_conf
     * */

    ngx_http_core_loc_conf_t *clcf; // main , server 或者 location 级别的配置块
    clcf = ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module);
// 宏：clcf = ((ngx_http_conf_ctx_t *)cf->ctx)->loc_conf[ngx_http_core_module.ctx_index]

    clcf->handler = ngx_http_mytest_handler;

    /*todo: 这里？*/
    ngx_conf_set_str_slot(cf,cmd,conf);
    return NGX_CONF_OK;
}


static ngx_command_t ngx_http_mytest_commands[] = {
        {
            ngx_string("mytest")
            NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
            ngx_http_mytest,
            /*todo: 暂时不明*/
            NGX_HTTP_LOC_CONF_OFFSET,
            offsetof(ngx_http_mytest_loc_conf_t, output_words),
            NULL,
        },
        ngx_null_command
};


struct ngx_module_s {
    ngx_uint_t ctx_index;
    ngx_uint_t index;
    char *name;
    ngx_unit_t spare0;
    ngx_unit_t spare1;
    ngx_unit_t version;
    const char *signature;
    // #define NGX_MODULE_V1 NGX_MODULE_UNSET_INDEX , NGX_MODULE_UNSET_INDEX , NULL , 0 , 0 ,nginx_version,NGX_MODULE_SIGNATURE;

    void *ctx;
    ngx_command_t *commands;
    ngx_unit_t type;
//    TODO: 七个阶段的执行

//    unitptr_t spare_hook0 -> spare_hook7
};
ngx_module_s ngx_http_mytest_module = {
        NGX_MODULE_V1,
        &ngx_http_mytest_module_ctx,
        NGX_HTTP_MODULE,
//      todo:七个阶段的执行
};