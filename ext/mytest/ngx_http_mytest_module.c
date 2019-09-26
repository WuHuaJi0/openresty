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

/* command */
static ngx_command_t ngx_http_mytest_commands[] = {
    {
        ngx_string("mytest"), // 指令名称
        NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1, //配置项类型，也就是决定可以出现的位置
        ngx_http_mytest, // 处理配置项的参数
        NGX_HTTP_LOC_CONF_OFFSET, //在配置文件中的偏移量
        offsetof(ngx_http_mytest_loc_conf_t, output_words), // 与解析配置文件有关，和上一个参数有关，之后详解
        NULL // 配置项读取后的处理方法
    },
    ngx_null_command // 数组结尾用 ngx_null_command 表示空的ngx_command_t :#define ngx_null_command {ngx_null_string,0,NULL,0,0,NULL}

};

/* 指令的回调函数 */
//疑问：cf ,cmd, conf 都是什么呢？
static char* ngx_http_mytest(ngx_conf_t* cf, ngx_command_t* cmd, void* conf) {
    //定义一个配置块变量: ngx_http_core_loc_conf_t 在 ngx_http_core_module.h 中
    ngx_http_core_loc_conf_t *clcf;

    //找到配置项所属的配置块，比如找到 location ?
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



// module 中的 ctx , http模块必须指向 ngx_http_module_t，定义在这里：
static ngx_http_module_t ngx_http_mytest_module_ctx = {
    NULL, // (*preconfiguration)(ngx_conf_t *cf); 解析配置文件前调用
    NULL, // (*postconfiguration)(ngx_conf_t *cf); 解析配置文件后调用
    NULL, // *(*create_main_conf)(ngx_conf_t *cf); 需要创建 数据结构用户存储 main 级别（直属http{}）的配置项时，可通过这里创建）
    NULL, // *(*init_main_conf)(ngx_conf_t *cf, void *conf); 初始化main级别的配置项
    NULL, // *(*create_srv_conf)(ngx_conf_t *cf); 需要创建数据结构存储于 server{}级别时
    NULL, //*(*merge_srv_conf)(ngx_conf_t *cf, void *prev, void *conf); 合并 main 级别和 server 级别的配置项
    ngx_http_mytest_create_loc_conf, // *(*create_loc_conf)(ngx_conf_t *cf); 创建 数据结构用户存储 location 级别 的配置项时
    ngx_http_mytest_merge_loc_conf // 合并 location 和 server
};

// Structure for the HelloWorld module, the most important thing
ngx_module_t ngx_http_mytest_module = {
        NGX_MODULE_V1, //定义在 core/ngx_module.h 包含了：
        //#define NGX_MODULE_V1                                                         \
//    NGX_MODULE_UNSET_INDEX, NGX_MODULE_UNSET_INDEX,                           \
//    NULL, 0, 0, nginx_version, NGX_MODULE_SIGNATURE
//        ngx_uint_t            ctx_index;
//        ngx_uint_t            index;
//        char                 *name;
//        ngx_uint_t            spare0;
//        ngx_uint_t            spare1;
//        ngx_uint_t            version;
//        const char           *signature;
        // ctx_index ,index, spare0 -> spare3 , version，signature
        &ngx_http_mytest_module_ctx, // *ctx 模块的上下文结构，http中 ctx 需要指向 ngx_http_module_t
        ngx_http_mytest_commands,// command 配置项
        NGX_HTTP_MODULE, // type: 和ctx设置有关，可以为一下5个值：NGX_HTTP_MODULE NGX_CORE_MODULE NGX_CONF_MODULE NGX_EVENT_MODULE NGX_MAIN_MODULE
        NULL, // (*init_master)(ngx_log_t *log) master进程启动回调，目前没有用到，设置为null
        NULL, // (*init_module)(ngx_cycle_t *cycle) 在初始化所有模块时调用
        NULL, // (*init_process)(ngx_cycle_t *cycle)
        NULL, // (*init_thread)(ngx_cycle_t *cycle)
        NULL, // (*exit_thread)(ngx_cycle_t *cycle)
        NULL, // (*exit_process)(ngx_cycle_t *cycle)
        NULL, // (*exit_master)(ngx_cycle_t *cycle)
        NGX_MODULE_V1_PADDING // spare_hook0 -> spare_hook7 ，保留字段都为 0
};


/*真正的处理函数*/
// ngx_ini_t 状态码，在 ngx_http_request 中
// 可返回标准的http状态码，也可以返回nginx自定义状态码,和Nginx全局状态码
static ngx_int_t ngx_http_mytest_handler(ngx_http_request_t* r) {
// r 代表请求的结构体 ,定义在 ngx_http_request.h

    ngx_int_t rsh; // result send header
    ngx_buf_t* b; // buf 处理大数据的关键数据结构 ，定义在 ngx_buf.h 中

    ngx_chain_t out[2]; // chain 与 buf 配合使用的数据结构，也定义在 ngx_buf 中 里面包含一个buf ，和一个chain(next) ,如果是最后一个chain,需要把 next置为 NULL

    ngx_http_mytest_loc_conf_t* hlcf; // 前面定义的，包含一个 string类型的 output_words
    hlcf = ngx_http_get_module_loc_conf(r, ngx_http_mytest_module); //

    /* 输出 headers: content_type */
    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char*)"text/plain";

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));

    out[0].buf = b;
    out[0].next = &out[1];

    b->pos = (u_char*)"mytest, "; //u_char 暂时找不到在哪定义的，理解为 unsigned char ； 被buf定义其实地址
    b->last = b->pos + sizeof("mytest, ") - 1; //buf 终止地址
    b->memory = 1; // 表示数据在内存中，且这段内存不可改

    // 分配内存
    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));

    out[1].buf = b;
    out[1].next = NULL;

    b->pos = hlcf->output_words.data;
    b->last = hlcf->output_words.data + (hlcf->output_words.len);
    b->memory = 1;
    b->last_buf = 1;

    /* 输出 status */
    r->headers_out.status = NGX_HTTP_OK;

    /* 输出 content_length */
    /* 问题：如何添加自定义头部？ */
    r->headers_out.content_length_n = hlcf->output_words.len + sizeof("mytest, ") - 1;

    // 发送响应
    rsh = ngx_http_send_header(r);
    if (rsh == NGX_ERROR || rsh > NGX_OK || r->header_only) {
        return rsh;
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