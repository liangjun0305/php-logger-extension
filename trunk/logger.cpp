/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2007 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id: header,v 1.16.2.1.2.1 2007/01/01 19:32:09 iliaa Exp $ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_logger.h"

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>

using namespace log4cxx;
//using namespace log4cxx::helpers;

// uncomment if using TS globals var
ZEND_DECLARE_MODULE_GLOBALS(logger)

/* NTS globals var */
zend_class_entry *basic_configurator_ce;
static int le_logger;

/* {{{ logger_functions[]
 *
 * Every user visible function must have an entry in logger_functions[].
 */
zend_function_entry logger_functions[] = {
	{NULL, NULL, NULL}	/* Must be the last line in logger_functions[] */
};
/* }}} */

/* {{{ logger_module_entry
 */
zend_module_entry logger_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
	STANDARD_MODULE_HEADER,
#endif
	PHP_LOGGER_EXTNAME,
	logger_functions,
	PHP_MINIT(logger),
	PHP_MSHUTDOWN(logger),
	PHP_RINIT(logger),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(logger),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(logger),
#if ZEND_MODULE_API_NO >= 20010901
	PHP_LOGGER_VERSION, /* Replace with version number for your extension */
#endif
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_LOGGER
ZEND_GET_MODULE(logger)
#endif


/* {{{ proto static void configure()
   Add a ConsoleAppender that uses Pattern Layout and prints to stdout to the root logger. */
static PHP_METHOD(LoggerBasicConfigurator, configure)
{
	BasicConfigurator::configure();
}

function_entry logger_basic_configurator_methods[] = {
	PHP_ME(LoggerBasicConfigurator, configure, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	{NULL, NULL, NULL}
};

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("logger.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_logger_globals, logger_globals)
    STD_PHP_INI_ENTRY("logger.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_logger_globals, logger_globals)
PHP_INI_END()
*/
/* }}} */

/* {{{ php_logger_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_logger_init_globals(zend_logger_globals *logger_globals)
{
	logger_globals->global_value = 0;
	logger_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(logger)
{
	zend_class_entry ce;

	/* initialize class LoggerBasicConfigurator */
	INIT_CLASS_ENTRY(ce, "LoggerBasicConfigurator", logger_basic_configurator_methods);
	basic_configurator_ce = zend_register_internal_class(&ce TSRMLS_CC);

	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(logger)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(logger)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(logger)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(logger)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "logger support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */