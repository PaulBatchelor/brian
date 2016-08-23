my @arr;

while(<>) {
    if(/^(.*): [^{]/) {
        push(@arr, $1);
    }
}

sub print_var
{
    my $name = shift @_;
    my $id = shift @_;
    my $sqlid = $id + 2;
    print <<END;
    tmp = get_val(&ar->val[$id]);
    char *$name = tmp.ud;
    sqlite3_bind_text(stmt, $sqlid, 
        $name, strlen($name), SQLITE_STATIC); 
END
}

sub make_sql
{
    my @q;
    $q[0] = "NULL";
    my $ref = shift @_;
    push(@q, "?");
    foreach (@$ref) {
        push(@q, "?");
    }
    $args = join(",", @q);
    print "\n";
    print <<END;
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(
         bd->db, 
         "INSERT INTO foo VALUES($args);",
         -1, 
         &stmt, NULL);
    sqlite3_bind_int64(stmt, 1, bd->id);
END
}

sub header {
    $arr = shift(@_);
    print("/*\n");
    print("CREATE TABLE foo(id INTEGER PRIMARY KEY,\n");
    print("bid INTEGER,\n");
    foreach (@$arr) {
        print("$_ TEXT,\n");
    }
    print(");\n");
    print("{\"foooo\",".scalar(@arr).",tbl_fooooo}\n");
    print("insert into sketches values(NULL, \"foo\");");
    print("*/\n");
    print <<END;
static int tbl_foo(brian_data *bd, brian_array *ar)
{
    brian_val tmp;
END

}

sub footer {
    print <<END;
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    
    return BRIAN_OK;
}
END
}

header(\@arr);
make_sql(\@arr);
foreach (0..scalar(@arr) - 1) 
{
    print_var($arr[$_], $_);
}
footer();
