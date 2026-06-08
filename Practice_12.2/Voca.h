/*
Voca.h
Date : 2026-06-05
Author : Lee Jong Kwang
- 단어와 관련된 정보를 저장하기 위한 클래스 정의
*/

#ifndef VOCA_H
#define VOCA_H
#include <iostream>
#include <string>
#include <regex>
#include <list>

/* 단어 타입 정의 */
enum Word_Type {
	NOUN, VERB, ADJ, ADV, PREPOS,
	WORD_TYPE_ERROR
};

/* 클래스 Voca */
typedef std::list<std::string> List_Str;
typedef std::list<std::string>::iterator Lst_Str_Itr;
class Voca {
	/* 출력을 위한 << 오버로딩 */
	friend std::ostream& operator<<(std::ostream& fout, const Voca& mv) {
		std::string wd_ty[] = { "n", "v", "adj", "adv", "prepos", "error" };
		std::list<std::string>::iterator itr;
		fout << mv.keyWord << "(" << wd_ty[mv.wordType] << "): \n";
		fout << " - thesaurus(";
		printStringList(fout, mv.thesaurus);
		fout << ")" << std::endl;
		fout << " - example usage(";
		printStringList(fout, mv.usages);
		fout << ")";
		return fout;
	}

public:
	/* 매개변수 생성자 */
	Voca(std::string kw, Word_Type wt, List_Str thes, List_Str ex_usg)
		:keyWord(kw), wordType(wt), thesaurus(thes), usages(ex_usg) {}
	/* 기본 생성자 */
	Voca() {}
	/* keyWord 반환 */
	const std::string getKeyWord() const { return keyWord; }
	/* wordType 반환 */
	Word_Type getWordType() const;
	/* thesaurus 반환 */
	const std::list<std::string>& getThesaurus() const { return this->thesaurus; }
	/* usages 반환 */
	const std::list<std::string>& getUsages() const { return this->usages; }
	/* keyWord 설정 */
	void setKeyWord(std::string kw) { this->keyWord = kw; }
	/* wordType 설정 */
	void setThesaurus(std::list<std::string> thes) { this->thesaurus = thes; }
	/* usages 설정 */
	void setUsages(std::list<std::string> usages) { this->usages = usages; }
	/* wordType 설정 */
	void setWordType(std::string wt) {
		Word_Type wordType;
		/* 단어 타입에 따라 저장 */
		if (wt == "NOUN") wordType = NOUN;
		else if (wt == "VERB") wordType = VERB;
		else if (wt == "ADJ") wordType = ADJ;
		else if (wt == "ADV") wordType = ADV;
		else if (wt == "PREPOS") wordType = PREPOS;
		else {
			std::cout << "Error in word_type : " << wt;
			std::cout << " is not implemented.yet !!!" << std::endl;
			wordType = WORD_TYPE_ERROR;
		} this->wordType =
			wordType;
	}

	/* 문자열 리스트를 출력하는 함수 */
	static void printStringList(std::ostream& fout,
		const std::list<std::string>& values) {
		bool first = true;
		for (const auto& value : values) {
			if (!first)
				fout << ", ";
			fout << value;
			first = false;
		}
	}

	/* 문자열에서 따옴표로 묶인 부분을 추출하는 함수 */
	std::list<std::string> extractQuotedStrings(const std::string& text) {
		std::list<std::string> result;
		
		/* 따옴표 추출 정규식 */
		std::regex itemPattern(R"(\"([^"]*)\")");
		auto begin = std::sregex_iterator(text.begin(), text.end(), itemPattern);
		auto end = std::sregex_iterator();
		for (auto it = begin; it != end; ++it) {
			result.push_back((*it)[1].str());
		}
		return result;
	}

	/* 정규식을 사용하여 한 줄을 파싱하는 함수 */
	bool parseLineByRegex(const std::string& line) {
		/* 한 줄 파싱 정규식 */
		std::regex linePattern(
			R"(^\s*([^,]+)\s*,\s*([^,]+)\s*,\s*\{([^}]*)\}\s*,?\s*\{([^}]*)\}\s*;\s*$)"
		);
		std::smatch match;
		if (!regex_match(line, match, linePattern)) {
			return false;
		}
		this->setKeyWord(match[1].str());
		this->setWordType(match[2].str());
		this->thesaurus = extractQuotedStrings(match[3].str());
		this->usages = extractQuotedStrings(match[4].str());
		return true;
	}
	int fgetVoca(const std::string& line) {
		bool res;
		res = parseLineByRegex(line);
		return res;
	}
private:
	std::string keyWord;  
	Word_Type wordType;
	std::list<std::string> thesaurus;  
	std::list<std::string> usages;
};
#endif