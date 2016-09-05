/* Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA */

#ifndef SQL_CALL_INCLUDED
#define SQL_CALL_INCLUDED

#include "sql_cmd_dml.h"    // Sql_cmd_dml
#include "sp_head.h"        // sp_name

class THD;

class Sql_cmd_call : public Sql_cmd_dml
{
public:
  explicit Sql_cmd_call(sp_name *proc_name_arg, List<Item> *prog_args_arg)
  : Sql_cmd_dml(), proc_name(proc_name_arg), proc_args(prog_args_arg)
  {}

  virtual enum_sql_command sql_command_code() const
  {
    return SQLCOM_CALL;
  }

  virtual bool is_data_change_stmt() const { return false; }

protected:
  virtual bool precheck(THD *thd);

  virtual bool prepare_inner(THD *thd);

  virtual bool execute_inner(THD *thd);

#if defined(HAVE_DTRACE) && !defined(DISABLE_DTRACE)
  virtual void start_stmt_dtrace(char *query)
  {}
  virtual void end_stmt_dtrace(int status, ulonglong rows, ulonglong changed)
  {}
#endif

private:
  sp_name *proc_name;
  List<Item> *proc_args;
};

#endif /* SQL_CALL_INCLUDED */
