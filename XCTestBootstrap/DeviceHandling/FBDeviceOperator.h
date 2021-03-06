/**
 * Copyright (c) 2015-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <Foundation/Foundation.h>

#import <FBControlCore/FBControlCore.h>

@class DTXTransport;
@class DVTAbstractiOSDevice;
@class FBProductBundle;
@class FBTestRunnerConfiguration;

NS_ASSUME_NONNULL_BEGIN

/**
 Operators are used to control devices
 */
@protocol FBDeviceOperator <NSObject>

/**
 Determines whether device supports testing with test manager daemon
 */
@property (nonatomic, assign, readonly) BOOL requiresTestDaemonMediationForTestHostConnection;

/**
 Starts test manager daemon and creates DTXTransport connection with it

 @param logger the Logger to Log to.
 @param error If there is an error, upon return contains an NSError object that describes the problem.
 @return DTXTransport if the operation succeeds, otherwise nil.
 */
- (nullable DTXTransport *)makeTransportForTestManagerServiceWithLogger:(id<FBControlCoreLogger>)logger error:(NSError **)error;

/**
 Queries application with given bundleID

 @param bundleID bundle ID of queried application
 @param error If there is an error, upon return contains an NSError object that describes the problem.
 @return applicationBundle if application is installed, otherwise nil
 */
- (nullable FBProductBundle *)applicationBundleWithBundleID:(NSString *)bundleID
                                                      error:(NSError *_Nullable *)error;

/**
 Returns PID of application with given bundleID

 @param bundleID bundle ID of installed application.
 @return A future wrapping the process id.
 */
- (FBFuture<NSNumber *> *)processIDWithBundleID:(NSString *)bundleID;

/**
 Returns the Crash Log for a given bundle id.
 This is used to augment the reporting of a test report with crash information.

 @param pid the Process ID of the potentially-crashed Application Process.
 @param bundleID the Bundle ID of the potentially-crashed Application Process.
 @param date the date to search for logs since.
 @return a Crash Log Info for the provided Bundle ID, nil otherwise.
 */
- (nullable FBDiagnostic *)attemptToFindCrashLogForProcess:(pid_t)pid bundleID:(NSString *)bundleID sinceDate:(NSDate *)date;

@end

NS_ASSUME_NONNULL_END
