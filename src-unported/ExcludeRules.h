/*
 *   File name: ExcludeRules.h
 *   Summary:	Support classes for QDirStat
 *   License:   GPL V2 - See file LICENSE for details.
 *
 *   Author:	Stefan Hundhammer <Stefan.Hundhammer@gmx.de>
 */


#ifndef ExcludeRules_h
#define ExcludeRules_h


#include <qstring.h>
#include <qregexp.h>
#include <qptrlist.h>


namespace QDirStat
{
    /**
     * One single exclude rule to check text (file names) against.
     * It can be enabled or disabled. Only enabled rules can ever match; a
     * disabled exclude rule will never exclude anything.
     **/
    class ExcludeRule
    {
    public:

	/**
	 * Constructor.
	 **/
	ExcludeRule( const QRegExp & regexp );

	/**
	 * Destructor.
	 **/
	virtual ~ExcludeRule();

	/**
	 * Check a string (usually a file name) against this exclude rule.
	 * Returns 'true' if the string matches, i.e. if the object this string
	 * belongs to should be excluded.
	 *
	 * Only enabled exclude rules will ever match; as long as it is
	 * disabled, this will always return 'false'.
	 **/
	bool match( const QString & text );

	/**
	 * Returns this rule's regular expression.
	 **/
	QRegExp regexp() const { return _regexp; }

	/**
	 * Change this rule's regular expression.
	 **/
	void setRegexp( const QRegExp & regexp ) { _regexp = regexp; }

	/**
	 * Check if this rule is enabled.
	 **/
	bool isEnabled() const { return _enabled; }

	/**
	 * Enable or disable this rule.
	 * New rules are always enabled by default.
	 **/
	void enable( bool enable = true ) { _enabled = enable; }


    private:

	QRegExp	_regexp;
	bool	_enabled;
    };


    /**
     * Container for multiple exclude rules.
     *
     * Normal usage:
     *
     *     ExcludeRules::excludeRules()->add( new ExcludeRule( ... ) );
     *     ...
     *     if ( ExcludeRules::excludeRules()->match( filename ) )
     *	   {
     *         // exclude this file
     *     }
     **/
    class ExcludeRules
    {
    public:

	/**
	 * Constructor.
	 *
	 * Most applications will want to use excludeRules() instead to create
	 * and use a singleton object of this class.
	 **/
	ExcludeRules();

	/**
	 * Destructor.
	 **/
	~ExcludeRules();

	/**
	 * Return the singleton object of this class.
	 * This will create one if there is none yet.
	 **/
	static ExcludeRules * excludeRules();

	/**
	 * Add an exclude rule to this rule set.
	 * This transfers ownership of that rule to this rule set;
	 * it will be destroyed with 'delete' after use.
	 **/
	void add( ExcludeRule * rule );

	/**
	 * Check a string against the exclude rules.
	 * This will return 'true' if the text matches any (enabled) rule.
	 *
	 * Note that this operation will move current().
	 **/
	bool match( const QString & text );

	/**
	 * Find the exclude rule that matches 'text'.
	 * Return 0 if there is no match.
	 *
	 * This is intended to explain to the user which rule matched.
	 **/
	const ExcludeRule * matchingRule( const QString & text );

	/**
	 * Returns the first exclude rule of this rule set
	 * or 0 if there is none.
	 **/
	ExcludeRule * first() { return _rules.first(); }
	
	/**
	 * Returns the next exclude rule (after first() or next() )
	 * of this rule set or 0 if there is no more.
	 **/
	ExcludeRule * next() { return _rules.next(); }
	
	/**
	 * Returns the current exclude rule of this rule set
	 * or 0 if there is none.
	 **/
	ExcludeRule * current() { return _rules.current(); }

	/**
	 * Clear (delete) all exclude rules.
	 **/
	void clear() { _rules.clear(); }

    private:

	QPtrList<ExcludeRule>    _rules;
    };

}	// namespace QDirStat


#endif // ifndef ExcludeRules_h

