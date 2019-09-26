#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

typedef struct {
    ngx_str_t print_string;
} ngx_http_print_loc_conf_t;

static void *ngx_http_print_create_loc_conf(ngx_conf_t *cf){
    ngx_http_print_loc_conf_t *conf;
    conf = ngx_pcalloc(cf->pool, sizeof(ngx_http_print_loc_conf_t));
    if( conf == NULL ){
        return NGX_CONF_ERROR;
    }
    conf->print_string.len = 0 ;
    conf->print_string.data = NULL;
    return conf;
}

static char *ngx_http_print_merge_loc_conf(ngx_conf_t *cf, void *parent, void *child){
    ngx_http_print_loc_conf_t *prev = parent;
    ngx_http_print_loc_conf_t *conf = child;
    ngx_conf_merge_str_value(conf->print_string,prev->print_string,"Nginx");
    return  NGX_CONF_OK;
}

static ngx_http_module_t ngx_http_print_module_ctx = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        ngx_http_print_create_loc_conf,
        ngx_http_print_merge_loc_conf,
};
static ngx_int_t ngx_http_print_handler(ngx_http_request_t *r){
    ngx_int_t rsh ; //result send header,
    ngx_buf_t *b; //buf

    ngx_chain_t out[2];
    ngx_http_print_loc_conf_t *config;
    config = ngx_http_get_module_loc_conf(r,ngx_http_print_module);

    r->headers_out.content_type.len = sizeof("text/plain") - 1;
    r->headers_out.content_type.data = (u_char*)"text/plain";

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    out[0].buf = b;
    out[0].next = &out[1];

//    todo : 把这里的hello输出去掉
    b->pos = (u_char*)"hello";
    b->last = b->pos + sizeof("hello") - 1;
    b->memory = 1;

    b = ngx_pcalloc(r->pool, sizeof(ngx_buf_t));
    out[1].buf = b;
    out[1].next = NULL;

    b->pos = config->print_string.data;
    b->last = config->print_string.data + (config->print_string.len);
    b->memory = 1;
    b->last_buf = 1;


    r->headers_out.status = NGX_HTTP_OK;
    r->headers_out.content_length_n = config->print_string.len + sizeof("hello");

    rsh = ngx_http_send_header(r);
    if( rsh == NGX_ERROR || rsh > NGX_OK || r->header_only ){
        return rsh;
    }

    return ngx_http_output_filter(r,&out[0]);



}
static char* ngx_http_print(ngx_conf_t *cf,ngx_command_t *cmd, void *conf){
ngx_http_core_loc_conf_t *clcf;

clcf = ngx_http_conf_get_module_loc_conf(cf,ngx_http_core_module);
clcf->handler = ngx_http_print_handler;

return NGX_CONF_OK;
}


static ngx_command_t ngx_http_print_commands[] = {
        {
                ngx_string("print"),
                NGX_HTTP_LOC_CONF | NGX_CONF_TAKE1,
                ngx_http_print,
                NGX_HTTP_LOC_CONF_OFFSET,
                offsetof(ngx_http_print_loc_conf_t, print_string);
        NULL,
        },
        ngx_null_command
};

ngx_module_t ngx_http_print_module = {
        NGX_MODULE_V1,
        &ngx_http_print_module_ctx,
        ngx_http_print_commands,
        NGX_HTTP_MODULE,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NGX_MODULE_V1_PADDING,
};



