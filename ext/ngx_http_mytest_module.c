
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

typedef struct {
    ngx_str_t output_words;
} ngx_http_mytest_loc_conf_t;


//struct ngx_command_s {
//    ngx_str_t             name;
//    ngx_uint_t            type;
//    char               *(*set)(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
//    ngx_uint_t            conf;
//    ngx_uint_t            offset;
//    void                 *post;
//};

//typedef struct ngx_command_s         ngx_command_t;

//#define NGX_HTTP_MAIN_CONF        0x02000000 main
//#define NGX_HTTP_SRV_CONF         0x04000000 server
//#define NGX_HTTP_LOC_CONF         0x08000000 location
//#define NGX_HTTP_UPS_CONF         0x10000000 upstrem
//#define NGX_HTTP_SIF_CONF         0x20000000 server if
//#define NGX_HTTP_LIF_CONF         0x40000000 location if
//#define NGX_HTTP_LMT_CONF         0x80000000 limit_except

//读取的参数个数
//#define NGX_CONF_NOARGS      0x00000001
//#define NGX_CONF_TAKE1       0x00000002
//#define NGX_CONF_TAKE2       0x00000004
//#define NGX_CONF_TAKE3       0x00000008
//#define NGX_CONF_TAKE4       0x00000010
//#define NGX_CONF_TAKE5       0x00000020
//#define NGX_CONF_TAKE6       0x00000040
//#define NGX_CONF_TAKE7       0x00000080

//Nginx处理HTTP的各个阶段
//typedef enum {
//    NGX_HTTP_POST_READ_PHASE = 0,
//
//    NGX_HTTP_SERVER_REWRITE_PHASE,
//
//    NGX_HTTP_FIND_CONFIG_PHASE,
//    NGX_HTTP_REWRITE_PHASE,
//    NGX_HTTP_POST_REWRITE_PHASE,
//
//    NGX_HTTP_PREACCESS_PHASE,
//
//    NGX_HTTP_ACCESS_PHASE,
//    NGX_HTTP_POST_ACCESS_PHASE,
//
//    NGX_HTTP_PRECONTENT_PHASE,
//
//    NGX_HTTP_CONTENT_PHASE,
//
//    NGX_HTTP_LOG_PHASE
//} ngx_http_phases;

/* command */
static ngx_command_t ngx_http_mytest_commands[] = {
    {
            ngx_string("mytest"), // 指令名称
            NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1, //配置项类型，也就是决定可以出现的位置
            ngx_http_mytest, //出现这个指令时执行的命令
            NGX_HTTP_LOC_CONF_OFFSET,
            offsetof(ngx_http_mytest_loc_conf_t, output_words),
            NULL
    },
    ngx_null_command // 数组结尾用 ngx_null_command 表示
};

/* 指令的回调函数 */
//疑问：cf ,cmd, conf 都是什么呢？
static char* ngx_http_mytest(ngx_conf_t* cf, ngx_command_t* cmd, void* conf) {
    //定义一个配置块变量
    ngx_http_core_loc_conf_t *clcf;
    //找到配置项所属的配置块
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);

    /*如果请求可以匹配到配置项，就调用这个方法处理请求*/
    clcf->handler = ngx_http_mytest_handler;

    /*这里干啥？*/
    ngx_conf_set_str_slot(cf, cmd, conf);
    return NGX_CONF_OK;
}


// To process HelloWorld command arguments
static char* ngx_http_mytest(ngx_conf_t* cf, ngx_command_t* cmd, void* conf);

// Allocate memory for HelloWorld command
static void* ngx_http_mytest_create_loc_conf(ngx_conf_t* cf);

// Copy HelloWorld argument to another place
static char* ngx_http_mytest_merge_loc_conf(ngx_conf_t* cf, void* parent, void* child);



// 各个阶段的回调方法
static ngx_http_module_t ngx_http_mytest_module_ctx = {
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    ngx_http_mytest_create_loc_conf,
    ngx_http_mytest_merge_loc_conf
};

// Structure for the HelloWorld module, the most important thing
ngx_module_t ngx_http_mytest_module = {
        NGX_MODULE_V1,
        &ngx_http_mytest_module_ctx,
        ngx_http_mytest_commands,
        NGX_HTTP_MODULE,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NGX_MODULE_V1_PADDING
};


/*真正的处理函数*/
// ngx_ini_t 状态码，在 ngx_http_request 中
// 可返回标准的http状态码，也可以返回nginx自定义状态码,和Nginx全局状态码
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t* r) {
    ngx_int_t rc;
    ngx_buf_t* b;
    ngx_chain_t out[2];

    ngx_http_mytest_loc_conf_t* hlcf;
    hlcf = ngx_http_get_module_loc_conf(r, ngx_http_mytest_module);

    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char*)"text/plain";

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));

    out[0].buf = b;
    out[0].next = &out[1];

    b->pos = (u_char*)"mytest, ";
    b->last = b->pos + sizeof("mytest, ") - 1;
    b->memory = 1;

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));

    out[1].buf = b;
    out[1].next = NULL;

    b->pos = hlcf->output_words.data;
    b->last = hlcf->output_words.data + (hlcf->output_words.len);
    b->memory = 1;
    b->last_buf = 1;

    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = hlcf->output_words.len + sizeof("mytest, ") - 1;
    rc = ngx_http_send_header(r);
    if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
        return rc;
    }

    return ngx_http_output_filter(r, &out[0]);
}

static void* ngx_http_mytest_create_loc_conf(ngx_conf_t* cf) {
    ngx_http_mytest_loc_conf_t* conf;

    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_mytest_loc_conf_t));
    if (conf == NULL) {
        return NGX_CONF_ERROR;
    }
    conf->output_words.len = 0;
    conf->output_words.data = NULL;

    return conf;
}

static char* ngx_http_mytest_merge_loc_conf(ngx_conf_t* cf, void* parent, void* child) {
    ngx_http_mytest_loc_conf_t* prev = parent;
    ngx_http_mytest_loc_conf_t* conf = child;
    ngx_conf_merge_str_value(conf->output_words, prev->output_words, "Nginx");
    return NGX_CONF_OK;
}