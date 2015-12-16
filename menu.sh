#!/bin/bash
#   This file is part of BOSS.
#
#    BOSS is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    BOSS is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with BOSS.  If not, see <http://www.gnu.org/licenses/>.

#PS3='Choice: '
#main_options=("Package Archive" "Translation Files" "Quit")
#translation_options=("Extract Strings" "Generate Translation Files" "Compile Translation Files" "Quit")
#generate_translation_options=("Create New Translation" "Update Existing Translation" "Quit")
choice=0
until [ "$choice" = "3" ]
#select main_opt in "${main_options[@]}"
do
	echo "Main Menu"
	echo "	1) Package Archive"
	echo "	2) Translation Files"
	echo "	3) Quit"

	echo -n "Choice: "
	read choice
	echo ""
	case $choice in
		1 | "Package Archive" | "package archive")
			;;
		2 | "Translation Files" | "translation files")
			#select tanslation_opt in "${translation_options[@]}"
			translation_choice=0
			until [ "$translation_choice" = "4" ]
			do
				echo "Translation Files"
				echo "	1) Extract Strings"
				echo "	2) Generate Translation Files"
				echo "	3) Compile Translation Files"
				echo "	4) Quit"

				echo -n "Choice: "
				read translation_choice
				echo ""
				case $translation_choice in
					1 | "Extract Strings" | "extract strings")
						;;
					2 | "Generate Translation Files" | "generate translation files")
						#select generate_translation_opt in "${generate_translation_options[@]}"
						generate_translation_choice=0
						until [ "$generate_translation_choice" = "3" ]
						do
							echo "Generate Translation FIles"
							echo "	1) Create New Translation"
							echo "	2) Update Existing Translation"
							echo "	3) Quit"

							echo -n "Choice: "
							read generate_translation_choice
							echo ""
							case $generate_translation_choice in
								1 | "Create New Translation" | "create new translation")
									;;
								2 | "Update Existing Translation" | "update existing translation")
									;;
								3 | "Quit" | "quit")
									generate_translation_choice=3
									break
									;;
								*)
									echo "Invalid Option"
									;;
							esac
						done
						;;
					3 | "Compile Translation Files" | "compile translation files")
						;;
					4 | "Quit" | "quit")
						translation_choice=4
						break
						;;
					*)
						echo "Invalid Option"
						;;
				esac
			done
			;;
		3 | "Quit" | "quit")
			choice=3
			break
			;;
		*)
			echo "Invalid Option"
			;;
	esac
done
