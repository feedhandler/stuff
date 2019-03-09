
#include "Utils.h"

#include <log4cpp/Category.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/PatternLayout.hh>

void initializeLogging()
{
  log4cpp::PatternLayout *layout = new log4cpp::PatternLayout();
  // show the thread ID (%t) in the log line
  layout->setConversionPattern("%d{%H:%M:%S.%L} %t [%c] %m%n");

  log4cpp::OstreamAppender *appender = new log4cpp::OstreamAppender("cout", &std::cout);
  appender->setLayout(layout);

  log4cpp::Category::getRoot().addAppender(appender);
}
