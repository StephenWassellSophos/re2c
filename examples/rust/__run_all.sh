root_dir=$(pwd)

for f in $(find -name '*.re'); do
    echo $f
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

    rustc "$rstest" && ./example 2>/dev/null || { echo "*** error ***"; exit 1; }

    rm -f "$rstest" example
    cd $root_dir
done

echo "All good."