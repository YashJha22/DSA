#!/bin/bash

set -e

REPO_ROOT="$(git rev-parse --show-toplevel)"
cd "$REPO_ROOT"

README="README.md"

echo "=== DSA GitHub Sync ==="

# Find uncommitted Java files, excluding generated/build directories
JAVA_FILES=$(git status --porcelain | awk '$1 ~ /A|M|\?\?/ {print $2}' | grep '\.java$' | grep -vE '^(out|build|\.idea)/' || true)

if [ -z "$JAVA_FILES" ]; then
    echo "No uncommitted Java solution found."
    echo "Nothing to sync."
    exit 0
fi

for FILE in $JAVA_FILES; do
    echo ""
    echo "Processing: $FILE"

    # Determine category from path
    if [[ "$FILE" == Basic/* ]]; then
        SECTION="Basic"
    elif [[ "$FILE" == src/Arrays/* ]]; then
        SECTION="Arrays"
    elif [[ "$FILE" == src/TwoPointers/* ]]; then
        SECTION="Two Pointers"
    elif [[ "$FILE" == src/SlidingWindow/* ]]; then
        SECTION="Sliding Window"
    else
        echo "Could not automatically determine README category for:"
        echo "$FILE"
        exit 1
    fi

    # Get filename without extension
    NAME=$(basename "$FILE" .java)

    # Convert common filename formats to readable problem names
    NAME=$(echo "$NAME" | sed -E 's/[-_]+/ /g')
    NAME=$(echo "$NAME" | sed -E 's/([a-z])([A-Z])/\1 \2/g')
    NAME=$(echo "$NAME" | sed -E 's/  +/ /g')

    # Capitalize first letter
    NAME="$(echo "$NAME" | awk '{for(i=1;i<=NF;i++){ $i=toupper(substr($i,1,1)) substr($i,2)} print}')"

    echo "Category: $SECTION"
    echo "Problem:  $NAME"

    # Compile
    echo "Compiling..."
    TEMP_OUT=$(mktemp -d)

    if ! javac -d "$TEMP_OUT" "$FILE"; then
        rm -rf "$TEMP_OUT"
        echo "Compilation failed. Nothing was committed."
        exit 1
    fi

    rm -rf "$TEMP_OUT"
    echo "Compilation successful."

    # Check whether README already contains this solution path
    if ! grep -Fq "\`$FILE\`" "$README"; then

        python3 - "$README" "$SECTION" "$NAME" "$FILE" <<'PY'
from pathlib import Path
import sys

readme = Path(sys.argv[1])
section = sys.argv[2]
name = sys.argv[3]
file_path = sys.argv[4]

text = readme.read_text()

entry = f"| {{number}} | {name} | `{file_path}` |"

# Find the target section
heading = f"### {section}"
start = text.find(heading)

if start == -1:
    # Create section before Objectives if it doesn't exist
    marker = "## Objectives"
    position = text.find(marker)

    if position == -1:
        raise SystemExit(f"Could not find section '{section}' or Objectives.")

    new_section = (
        f"### {section}\n\n"
        "| # | Problem | Solution |\n"
        "|---|---|---|\n"
        f"| 1 | {name} | `{file_path}` |\n\n"
    )

    text = text[:position] + new_section + text[position:]
else:
    # Find end of section
    next_heading = text.find("\n### ", start + len(heading))

    if next_heading == -1:
        end = len(text)
    else:
        end = next_heading

    section_text = text[start:end]

    # Determine next table number
    import re
    numbers = [
        int(x)
        for x in re.findall(r'^\| (\d+) \|', section_text, re.MULTILINE)
    ]

    next_number = max(numbers) + 1 if numbers else 1

    new_entry = (
        f"| {next_number} | {name} | `{file_path}` |\n"
    )

    # Insert after the last table row
    lines = section_text.rstrip().splitlines()

    insert_at = len(lines)

    for i in range(len(lines) - 1, -1, -1):
        if lines[i].startswith("|"):
            insert_at = i + 1
            break

    lines.insert(insert_at, new_entry.rstrip())

    updated_section = "\n".join(lines) + "\n\n"
    text = text[:start] + updated_section + text[end:]

readme.write_text(text)
PY

        echo "README updated."
    else
        echo "README already contains this solution."
    fi

    # Solution commit
    git add "$FILE"
    git commit -m "feat: add $NAME solution"

done

# README commit if changed
if ! git diff --quiet README.md; then
    git add README.md
    git commit -m "docs: update README"
else
    echo "No README changes needed."
fi

echo ""
echo "Pushing to GitHub..."
git push origin main

echo ""
echo "=== Final Status ==="
git status

echo ""
echo "Done."
