root_dir=$(pwd)

for f in $(find -name '[0123456789]*.re'); do
    cd $(dirname $f)

    rsfile="$(basename ${f%.re}.rs)"
    rstest="example.rs"

    cat "$rsfile" \
        | egrep -v 'warning: rule .*matches empty string \[-Wmatch-empty-string\]' \
        | egrep -v 'warning: tag .* degree of nondeterminism \[-Wnondeterministic-tags\]' \
        > "$rstest"

    # If the autogenerated message appears more than once in the file, then
    # it must have autogenerated header appended at the end. Cut it off.
    msg='Generated by re2c'
    if [ $(grep -c "$msg" "$rstest") -gt 1 ]; then
        # Get the line of the second message occurrence.
        l=$(grep -n "$msg" "$rstest" | tail -n +2 | cut -d : -f 1)
        # Cut off everything past that line.
        head -n $l "$rstest" > "$rstest".mod && mv "$rstest".mod "$rstest"
    fi

    echo "$f"
    rustc "$rstest" && ./example || { echo "*** error ***"; exit 1; }

    # patch YYPEEK definition: `unsafe {*s.get_unchecked(cursor)}` -> `s[cursor]`
    sed -E 's/unsafe \{\*([^ ]+).get_unchecked\(([^ ]+)\)\}/\1[\2]/' -i "$rstest"

    echo "$f (with bounds checks)"
    rustc "$rstest" && ./example || { echo "*** error ***"; exit 1; }

    rm -f "$rstest" example
    cd $root_dir
done

echo "All good."
